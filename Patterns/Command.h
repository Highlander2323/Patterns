#pragma once
#include <iostream>

class Executor {
	std::string prompt = "";
public:
	void writeA() {
		prompt += "A";
		std::cout << prompt << std::endl;
	}

	void writeB() {
		prompt += "B";
		std::cout << prompt << std::endl;
	}

	std::string& getPrompt() {
		return prompt;
	}
};


class Command {
protected:
	Executor* exec;
public:
	Command(Executor* e) : exec(e) {}
	virtual void execute() = 0;
	virtual void undo() = 0;
};

class CommandHistory {
	Command** commands = nullptr;
	unsigned int length = 0;
	static CommandHistory* instance;

	CommandHistory() {
	}
public:
	~CommandHistory() {
		instance = nullptr;
		delete[] commands;
	}

	static CommandHistory* get() {
		if (instance == NULL) {
			instance = new CommandHistory();
		}
		return instance;
	}

	void showAll() {
		for (auto i = 0; i < length; i++) {
			commands[i]->execute();
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void push(Command* c) {
		if (length == 0) {
			commands = new Command * [1]();
			commands[0] = c;
			length++;
			return;
		}

		Command** alt = new Command *[length+1] ();
		for (unsigned int i = 0; i < length; i++) {
			alt[i] = commands[i];
		}

		alt[length] = c;

		delete[] commands;

		commands = alt;
		length++;
	}

	Command* pop() {
		if (length == 0) {
			return nullptr;
		}

		Command* c;

		if (length - 1 == 0) {
			c = commands[0];
			delete[] commands;
			length--;
			return c;
		}

		Command** alt = new Command * [length - 1]();
		for (unsigned int i = 0; i < length - 1; i++) {
			alt[i] = commands[i];
		}
		c = commands[length - 1];

		delete[] commands;

		length--;
		commands = alt;
		return c;
	}
};

CommandHistory* CommandHistory::instance = nullptr;


class CommandA : public Command {
public:
	CommandA(Executor* exec) : Command(exec) {}

	virtual void execute() override {
		exec->writeA();
		CommandHistory::get()->push(this);
	}

	virtual void undo() override {
		exec->getPrompt().pop_back();
		std::cout << exec->getPrompt() << std::endl;
	}
};

class CommandB : public Command{
public:
	CommandB(Executor* exec) : Command(exec) {}

	virtual void execute() override {
		exec->writeB();
		CommandHistory::get()->push(this);
	}

	virtual void undo() override {
		exec->getPrompt().pop_back();
		std::cout << exec->getPrompt()<< std::endl;
	}
};

class Menu {
public:
	void clickA(Executor* e) {
		Command* com = new CommandA(e);
		com->execute();
	}

	void clickB(Executor* e) {
		Command* com = new CommandB(e);
		com->execute();
	}

	void undo(Command* com) {
		com->undo();
	}
};

//---RUN THIS---
class RunThis{
public:
	static void go() {
		Executor* exec = new Executor();
		Menu* menu = new Menu();
		menu->clickA(exec);
		menu->clickB(exec);
		menu->clickA(exec);
		menu->clickB(exec);
		menu->clickA(exec);
		menu->clickA(exec);
		menu->clickB(exec);
		menu->clickB(exec);
		menu->undo(new CommandA(exec));
		menu->undo(new CommandA(exec));
		menu->undo(new CommandA(exec));
		menu->undo(new CommandA(exec));
	}
};