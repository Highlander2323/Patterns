#pragma once
#include <iostream>
#include <unordered_map>

class Context {
	std::unordered_map<std::string, bool> variables;
public:

	void assign(std::string name, bool value) {
		variables[name] =  value;
	}

	bool get(std::string name) {
		return variables[name];
	}
};

//Abstract root class
class BooleanExp {
public:
	virtual bool interpret(Context&) = 0;
};

class Constant : public BooleanExp {
	bool value;
public:
	Constant(bool value_) : value(value_) {};

	virtual bool interpret(Context& ctx) {
		return value;
	}
};

class VariableExp : public BooleanExp {
	std::string name;
public:

	VariableExp(std::string name_) : name(name_){};

	virtual bool interpret(Context& ctx) override{
		return ctx.get(name);
	}
};


class OrExp : public BooleanExp {
	BooleanExp* op1,* op2;
public:
	OrExp(BooleanExp* op1_, BooleanExp* op2_) : op1(op1_), op2(op2_) {}

	virtual bool interpret(Context& ctx) override {
		return op1->interpret(ctx) || op2->interpret(ctx);
	}
};


class AndExp : public BooleanExp {
	BooleanExp* op1, * op2;
public:
	AndExp(BooleanExp* op1_, BooleanExp* op2_) : op1(op1_), op2(op2_) {}

	virtual bool interpret(Context& ctx) override {
		return op1->interpret(ctx) && op2->interpret(ctx);
	}
};

class NotExp : public BooleanExp {
	BooleanExp* exp;
public:
	NotExp(BooleanExp* exp_) : exp(exp_) {}

	virtual bool interpret(Context& ctx) override {
		return !exp->interpret(ctx);
	}
};

class RunThis {
public:

	// ((a OR b) AND ((a OR not b) AND true))
	static void go() {
		Context ctx;
		ctx.assign("a", false);
		ctx.assign("b", false);

		BooleanExp* exp;

		exp = new AndExp(new OrExp(new VariableExp("a"), new VariableExp("b")),
			new AndExp(new OrExp(new VariableExp("a"), new NotExp(new VariableExp("b"))), new Constant(true)));

		std::cout << exp->interpret(ctx);

		delete exp;
	}
};