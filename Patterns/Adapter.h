#pragma once
#include <iostream>
#include <vector>

class AmericanDate {
protected:
	std::string americanDate = "09/11/2023";
public:
	std::string getAmericanDate() {
		return "American Format Date: " + americanDate + "\nMAKE AMERICA GREAT AGAIN!!!\n";
	}
};

class LocalDate {
	std::string europeanDate;
public:
	std::string getEuropeanDate() {
		return "European Format Date: " + europeanDate + "\nAmericans are weird...\n";
	}

	void setDate(std::string d) {
		europeanDate = d;
	}

};

class Adapter: AmericanDate, public LocalDate {
public:

	std::string tokenize(std::string& str, char c) {
		std::vector<std::string> v;
		std::string word;
		for (auto i = 0; i < str.size(); i++) {
			if (str[i] == c) {
				v.push_back(word);
				word.clear();
			}
			else { 
				word += str[i]; }
		}
		v.push_back(word);
		return v[1] + '/' + v[0] + '/' + v[2];;
	}

	void adaptDate() {
		setDate(tokenize(americanDate, '/'));
	}

	void display() {
		std::cout << getAmericanDate() << std::endl << getEuropeanDate();
	}

};