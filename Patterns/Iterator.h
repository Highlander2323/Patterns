#pragma once
#include <iostream>
#include <fstream>


class Cat {
	std::string name;
	std::string breed;
	unsigned short age;
public:
	Cat(std::string name_ = "Snuffles", std::string breed_ = "Orange", unsigned short age_ = 1) :
		name(name_), breed(breed_), age(age_){}

	void print() {
		std::cout << std::endl << "Cat's name: " << name << std::endl
			<< "Cat's breed: " << breed << std::endl
			<< "Cat's age: " << age << "\n\n";
	}
};

template <class Item>
class List {
	Item* items;
	long n;
public:
	List() : items(nullptr), n(0){}

	List(Item* items_) {
		long n = 0;
		for (auto i : items_) {
			n++;
		}

		items = new Item[n]();

		for (long i = 0; i < n; i++ ) {
			items[i] = items_[i];
		}
	}

	long count() const {
		return n;
	}

	Item& get(long cursor) {
		return items[cursor];
	}

	void append(const Item& item) {
		if (items == nullptr) {
			items = new Item(item);
			n++;
			return;
		}

		Item* aux = new Item[n + 1]();

		for (long i = 0; i < n; i++) {
			aux[i] = items[i];
		}

		aux[n] = item;

		if (n == 1) {
			delete items;
		}
		else {
			delete[] items;
		}
		items = aux;
		n++;
	}

	void pop() {
		if (n == 0) {
			return;
		}

		if (n == 1) {
			delete[] items;
			items = nullptr;
			n--;
			return;
		}

		Item* aux = new Item[n - 1]();

		for (long i = 0; i < n - 1; i++) {
			aux[i] = items[i];
		}
		delete[] items;
		items = aux;
		n--;
	}
};

template <class Item>
class Iterator {
	unsigned long current;
protected:
	Iterator() {};
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual bool isDone() const = 0;
	virtual Item currentItem() const = 0;
};

template <class Item>
class ListIterator : public Iterator<Item> {
	List<Item>* list;
	long current;
public:
	ListIterator(List<Item>* list_) : list(list_) { current = 0; };

	virtual void first() override {
		current = 0;
	}

	virtual void next() override {
		current++;
	}

	virtual bool isDone() const override {
		return current >= list->count();
	}

	virtual Item currentItem() const override {
		return list->get(current);
	}
};


class RunThis {
public:
	static void Go() {
		std::ifstream in("Cats.txt");
		std::string name, breed;
		unsigned short age;
		Cat* cat;
		List<Cat>* list = new List<Cat>();
		while (in >> name >> breed >> age) {
			cat = new Cat(name, breed, age);
			list->append(*cat);
			delete cat;
		}

		ListIterator<Cat> iterator(list);

		for (iterator.first(); !iterator.isDone(); iterator.next()) {
			iterator.currentItem().print();
		}
	}
};
