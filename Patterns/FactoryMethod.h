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

	//Parse the date as string and return the result as a string of format DD.MM.YYYY
	string parseDateString() {
		string text = to_string(day);
		text += "." + parseMonthString(month) + "." + to_string(year);
		return text;
	}
};

class Reservation {
protected:
	Date checkIn;
	Date checkOut;
	string name;
	int numberOfRooms;

public:

	void setPeriod(Date in, Date out) {
		checkIn = in;
		checkOut = out;
	}

	void setNum(unsigned short num) {
		numberOfRooms = num;
	}

	void setName(string name) {
		this->name = name;
	}

	void initRes(Date in, Date out, string name, int num) {
		setPeriod(in, out);
		setNum(num);
		setName(name);
	}

	virtual void display() = 0;
};


class DoubleRoomReservation : public Reservation {

public:
	void display() {
		cout << "The reservation(double rooms) for " << name << " is:"
			<< "\nNumber of rooms: " << numberOfRooms
			<< "\nPeriod: " << checkIn.parseDateString() << " - " << checkOut.parseDateString() << '\n';
	}


};

class TripleRoomReservation : public Reservation {

public:
	void display() {
		cout << "The reservation(triple rooms) for " << name << " is:"
			<< "\nNumber of rooms: " << numberOfRooms
			<< "\nPeriod: " << checkIn.parseDateString() << " - " << checkOut.parseDateString() << '\n';
	}

};


class ReservationCreator {
public:
	virtual Reservation* createReservation() = 0;
};

class DoubleRoomReservationCreator : public ReservationCreator {
public:
	virtual Reservation* createReservation() {
		return new DoubleRoomReservation;
	}
};

class TripleRoomResercationCreator : public ReservationCreator {
public:
	virtual Reservation* createReservation() {
		return new TripleRoomReservation;
	}
};



