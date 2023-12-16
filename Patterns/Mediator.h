#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

std::ifstream file("Countries.txt");

class Mediator;

class Widget {
protected:
	Mediator* mediator;
public:
	Widget(Mediator* med = nullptr) {
		mediator = med;
	}
	void setMediator(Mediator* med) {
		mediator = med;
	}
};

class TextBox : public Widget{
	std::string text;
public:
	TextBox(std::string text_ = "TextBox") : text(text_){
	}

	void setText(std::string text_) {
		text = text_;
	}

	void draw() {
		std::cout << "--";
		for (int i = 0; i < text.size(); i++)
			std::cout << '-';
		std::cout << "--\n  " << text << "  \n--";
		for (int i = 0; i < text.size(); i++)
			std::cout << '-';
		std::cout << "--";
	}
};

class DropText : public Widget{
	std::string* strings;
	std::string selected = "";
	unsigned int n;
public:
	~DropText() {
		if (n == 1) {
			delete strings;
		}
		else {
			delete[] strings;
		}
	}
	DropText(std::string* strings_, unsigned int n_ = 1){
		if (n_ == 1) {
			strings = new std::string();
			strings = strings_;
		}
		else {
			strings = new std::string[n_]();
			for (unsigned int i = 0; i < n_; i++) {
				strings[i] = strings_[i];
			}
		}
		n = n_;
	}

	void initialize();

	void select(unsigned int n);

	std::string getSelected() {
		return selected;
	}
};

class Button : public Widget{
public:
	Button(){}
	
	void onClick();
};

class Mediator {
	Button* button;
	DropText* drop;
	TextBox* box;
public:

	Mediator(Button* button_, DropText* drop_, TextBox* box_) :
		button(button_), drop(drop_), box(box_)
	{
		button->setMediator(this);
		drop->setMediator(this);
		box->setMediator(this);
	}

	void notify(Widget* sender, std::string event) {
		if (sender == button && event == "Button pressed") {
			if (drop->getSelected() == "") {
				std::cout << "No coutry selected\n";
			}
			else {
				box->draw();
			}
		}
		else if (sender == drop && event == "Selected") {
			box->setText(drop->getSelected());
		}
		else if (sender == drop && event == "Button pressed") {
			box->draw();
		}
	}
};

void DropText::select(unsigned int n = 0) {
	selected = strings[n];
	mediator->notify(this, "Selected");
}

void DropText::initialize() {
	unsigned int opt;
	std::cout << "\nSelect a country:\n";
	for (unsigned int i = 0; i < n; i++) {
		std::cout << i + 1 << ") " << strings[i] << "\n";
	}
	std::cout << "0) Press Button\n>>>";
	std::cin >> opt;
	if (opt != 0) {
		select(opt - 1);
	}
	else {
		mediator->notify(this, "Button pressed");
	}
}

void Button::onClick() {
	std::cout << "\nButton pressed\n";
	mediator->notify(this, "Button pressed");
}

class RunThis {
public:
	static void go() {
		unsigned int n;
		file >> n;
		std::string* strings = new std::string[n]();
		for (unsigned int i = 0; i < n; i++) {
			file >> strings[i];
		}

		DropText* drop = new DropText(strings, n);
		TextBox* box = new TextBox();
		Button* button = new Button();

		Mediator* mediator = new Mediator(button, drop, box);

		drop->initialize();
		button->onClick();

		delete[] strings;
		delete drop;
		delete box;
		delete button;
		delete mediator;
	}
};