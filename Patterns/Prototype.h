#pragma once
#include <iostream>
#include <string>

//Enum for options
enum Option {QUIT, BIKE, BOAT};


//prototype abstract class
class Reservation {
protected:
	unsigned int price;
	std::string model;

public:

	Reservation() {
		std::cout << "CREATED";
	}

	Reservation(Reservation* res) {
		this->model = res->model;
		this->price = res->price;
	}


	void setModel(std::string name) {
		this->model = name;
	}

	void setPrice(unsigned int p) {
		this->price = p;
	}

	void initRes(std::string name, unsigned int price) {
		setModel(name);
		setPrice(price);
	}

	virtual Reservation* clone() = 0;

	virtual void display() = 0;
};


//Prototype concrete class 1
class BoatReservation : public Reservation {
public:
	BoatReservation() { 
		std::cout << " BOAT RESERVATION\n"; }
	BoatReservation(BoatReservation* res) : Reservation(res) {
	}

	void display() {
		std::cout << "The boat reservation for model" << model << " is:"
			<< "\nPrice: " << price << std::endl;
	}

	virtual Reservation* clone() {
		return new BoatReservation(this);
	}

};


//Prototype concrete class 2
class BikeReservation : public Reservation {
public:

	BikeReservation() { 
	std::cout << " BIKE RESERVATION\n"; }

	BikeReservation(BikeReservation* res) : Reservation(res){
	}

	void display() {
		std::cout << "The bike reservation for model" << model << " is:"
			<< "\nPrice: " << price << std::endl;
	}

	virtual Reservation* clone() {
		return new BikeReservation(this);
	}

};


class ReservationMaker {
	Reservation** storage;
	Reservation** reservations;
	unsigned int max = 0;
public:
	void initialize() {
		if (storage == nullptr) {
			storage = new Reservation*[2];
			BikeReservation bike;
			bike.initRes("Pegasus", 20);
			BoatReservation boat;
			boat.initRes("Yamaha", 100);
			storage[0] = &bike;
			storage[1] = &boat;
		}

		while (true) {
			unsigned int opt;
			std::cout << "\nCHOOSE:\n0 - DISPLAY & EXIT\n1 - BIKE RESERVATION\n2 - BOAT RESERVATION\n>>>";
			std::cin >> opt;
			if (opt > 2 || opt == 0) {
				break;
			}
			else {
				createReservation((Option)opt);
			}
		}
	}

	void createReservation(Option opt) {
		max++;
		if (reservations == nullptr) {
			reservations = new Reservation*;
			switch (opt) {
			case BIKE:
				reservations[0] = storage[0]->clone();
				break;
			case BOAT:
				reservations[0] = storage[1]->clone();
				break;
			}
			return;
		}
		
		Reservation** newRes = new Reservation* [max];
		for (unsigned int i = 0; i < max - 1; i++) {
			newRes[i] = reservations[i];
		}

		switch (opt) {
		case BIKE:
			newRes[max - 1] = storage[0]->clone();
			break;
		case BOAT:
			newRes[max - 1] = storage[1]->clone();
			break;
		}

		reservations = newRes;
	}

	void display() {
		for (unsigned int i = 0; i < max; i++) {
			reservations[i]->display();
		}

	};
};
