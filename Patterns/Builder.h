#pragma once
#include <iostream>
#include <string>
using namespace std;

//Enum for months of the year.
enum Month { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };


//Struct that defines dates in european format DD-MM-YYYY
struct Date {
	unsigned short minute, hour;
	unsigned short day : 5;
	Month month;
	unsigned short year : 12;

	Date() {
		minute = 0;
		hour = 0;
		day = 1;
		month = JAN;
		year = 1997;
	}

	//Parse the month as a string, returning the format as MM
	// (Months that represent one digit are preceded by a '0')
	static string parseMonthString(Month m) {
		if (m + 1 > 9) {
			return to_string(m + 1);
		}
		else return "0" + to_string(m + 1);
	}

	//Parse the date as string and return the resulkt as a string of format DD.MM.YYYY
	string parseDateString() {
		string text = to_string(day);
		text += "." + parseMonthString(month) + "." + to_string(year);
		return text;
	}
};

//Product 1
class Reservation {
private:
	unsigned short max;
	Date checkIn, checkOut;
	unsigned short numberOfRooms;
	string nameOfReservation;
public:
	Reservation() {
		nameOfReservation = "GENERIC";
		numberOfRooms = 0;
	}

	void setMax(unsigned short m) {
		max = m;
	}

	void setPeriod(Date in, Date out) {
		checkIn = in;
		checkOut = out;
	}

	void setNum(unsigned short num) {
		numberOfRooms = num;
	}

	void setName(string name) {
		nameOfReservation = name;
	}

	void display() {
		cout << "The reservation for " << nameOfReservation << " is:"
			<< "\nNumber of rooms: " << numberOfRooms
			<< "\nPeriod: " << checkIn.parseDateString() << " - " << checkOut.parseDateString() << '\n';
	}

};



//Abstract Builder
class ReservationBuilder {
public:
	virtual void setMax(unsigned short) {};
	virtual void setRoomNum(unsigned short) {};
	virtual void setResName(string) {};
	virtual void setResPeriod(Date, Date) {};
	virtual void setResTime(Date, Date) {};
	virtual Reservation* getRes() { return nullptr; };
	virtual void buildRes() {};
protected:
	ReservationBuilder() {};
};


//Concrete Builder 1 - Two Person Bedroom Reservation
class TwoPersonBuilder : public ReservationBuilder {
private:
	Reservation* res;

public:
	virtual void setRoomNum() {
		res->setNum(8);
	}

	virtual void setResName(string name) {
		res->setName(name);
	}

	virtual void setResPeriod(Date in, Date out) {
		res->setPeriod(in, out);
	}

	virtual void buildRes() {
		res = new Reservation;
	}

	virtual Reservation* getRes() {
		return res;
	}
};


//Concrete Builder 2 - Three Person Bedroom Reservation
class ThreePersonBuilder : public ReservationBuilder {
private:
	Reservation* res;

public:
	virtual void setMax() {
		res->setMax(6);
	}

	virtual void setRoomNum(unsigned short num) {
		res->setNum(num);
	}

	virtual void setResName(string name) {
		res->setName(name);
	}

	virtual void setResPeriod(Date in, Date out) {
		res->setPeriod(in, out);
	}

	virtual void buildRes() {
		res = new Reservation;
	}

	virtual Reservation* getRes() {
		return res;
	}
};

//Director - Here we have the builder member
class ReservationsManager {
	ReservationBuilder* builder;

public:
	void setBuilder(ReservationBuilder& b) {
		builder = &b;
	}

	Reservation* getRes() {
		return builder->getRes();
	}

	void createReservation() {
		Date in, out;
		in.day = 23;
		in.month = JUL;
		in.year = 2023;
		out.day = 29;
		out.month = JUL;
		out.year = 2023;
		builder->buildRes();
		builder->setResName("Andra");
		builder->setResPeriod(in, out);
		builder->setRoomNum(2);
	}
};