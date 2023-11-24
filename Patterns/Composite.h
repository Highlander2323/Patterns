#pragma once
#include <iostream>
#include <vector>
#include <iterator>


enum Rarity{None, Common, Rare, Epic, Legendary};

class Item {
	unsigned int id;
protected:
	void setId(unsigned int id) {
		this->id = id;
	}

	Item() { setId(0); };
public:

	virtual ~Item() {
		delete this;
	};

	virtual bool isBag() = 0;

	unsigned int getId() {
		return id;
	};

	virtual Rarity getRarity() { return None; };
	virtual unsigned int getPrice() = 0;

};

class Coin : public Item {
public:

	Coin() {
		setId(2);
	}

	virtual bool isBag() {
		return false;
	}

	virtual Rarity getRarity() {
		return Common;
	}

	virtual unsigned int getPrice() {
		return 1;
	}
};

class Gem : public Item {
public:

	Gem() {
		setId(2);
	}

	virtual bool isBag() {
		return false;
	}

	virtual Rarity getRarity() {
		return Epic;
	}

	virtual unsigned int getPrice() {
		return 100;
	}
};

class Excalibur : public Item {
public:
	Excalibur() {
		setId(3);
	}

	virtual bool isBag() {
		return false;
	}

	virtual Rarity getRarity() {
		return Legendary;
	}

	virtual unsigned int getPrice() {
		return 1800;
	}
};

class CompoundItem : public Item{
protected:
	std::vector<Item*> children;

	CompoundItem() {};
public:
	virtual void add(Item* i) {
		children.push_back(i);
	};

	virtual bool isBag() {
		return false;
	};

	virtual void remove(Item* i) {
		for (auto item = children.begin(); item != children.end(); item++)
			if (i == *item) {
				children.erase(item);
				break;
			}
		
	};

	virtual unsigned int getPrice() {
		unsigned int count = 0;
		for (auto child : children) {
			count += child->getPrice();
		}
		return count;
	}
};

class Pouch : public CompoundItem{
	
public:
	virtual ~Pouch() {
		for (auto i : children) {
			delete i;
		}
	}

	virtual bool isBag() {
		return false;
	}

	virtual void add(Item* i) {
		try {
			if (i->isBag()) {
				throw std::invalid_argument("Bag is too big to be added into pouch!");
			}

			children.push_back(i);
		}
		catch (std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
		}
	};
};

class Bag : public CompoundItem {

public:
	virtual ~Bag() {
		for (auto i : children) {
			delete i;
		}
	}

	virtual bool isBag() {
		return true;
	}


};