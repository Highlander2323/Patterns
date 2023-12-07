#pragma once
#include <iostream>
#include <vector>

enum Rarity { None, Common, Rare, Epic, Legendary };

class Item {
	unsigned int id;
	std::string sprite;
public:
	Item() {
	};

	Item(unsigned int id, std::string sprite) {
		this->id = id;
		this->sprite = sprite;
	};

	unsigned int getId() {
		return id;
	};

	std::string getSprite() {
		return sprite;
	};
};

class ItemFactory {
	static std::vector<Item*> items;

	static Item* find(unsigned int id, std::string sprite) {
		for (Item* item : items) {
			if (item->getId() == id && item->getSprite() == sprite) {
				return item;
			}
		}
		return nullptr;
	}

public:
	static Item* getItem(unsigned int id, std::string sprite) {
		Item* i = find(id, sprite);
		if (i == nullptr) {
			i = new Item(id, sprite);
			items.push_back(i);
		}
		return i;
	}
};

std::vector<Item*> ItemFactory::items;

class Gem : public Item {
	float price;
	Rarity rarity;
public:

	Gem(unsigned int i, std::string s, float p, Rarity r) : Item(i, s), price(p), rarity(r) {};

	float getPrice() {
		return price;
	}

	Rarity getRarity() {
		return rarity;
	}
};

class Sword : public Item {
	float damage;
	Rarity rarity;
public:
	Sword(unsigned int i, std::string s, float d, Rarity r) : Item(i, s), damage(d), rarity(r) {};

	float getDamage() {
		return damage;
	}

	Rarity getRarity() {
		return rarity;
	}
};