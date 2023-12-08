#pragma once
#include <iostream>
#include <fstream>

//Dummy Sprite class
class Sprite {
	std::string fileName;
public:
	Sprite(std::string file) {
		fileName = file;
	}

	void draw() {
		std::ifstream infile(fileName);
		char value;
		while (infile.get(value))
			std::cout << value;
		std::cout<< "\n\n";
	}
};



//Abstract base class for Real subject and Proxy
class Character {
protected:
	Sprite* sprite = 0;
public:
	virtual void draw() = 0;
};

//Real subject class
class GameObject : public Character{
public:
	GameObject(std::string fileName) {
		sprite = new Sprite(fileName);
	}

	~GameObject() {
		delete sprite;
	}

	virtual void draw() {
		sprite->draw();
	};
};

//Proxy class
class Placeholder : public Character {
	GameObject* character;
	std::string fileName;
	bool detected;

	void initializeCharacter() {
		character = getCharacter();
	}

public:
	Placeholder(std::string file = "Placeholder.txt") {
		character = 0;
		fileName = file;
		detected = false;
	}

	void detect() {
		detected = true;
	}

	GameObject* getCharacter() {
		if (character == 0)
			character = new GameObject(fileName);
		return character;
	}

	virtual void draw() {
		if (detected) {
			initializeCharacter();
			character->draw();
		}
		else {
			std::cout << "Drawable not in view\n\n";
		}
	};
};
