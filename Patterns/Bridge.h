#pragma once
#include <iostream>
#include <vector>

class Database {
protected:
	std::string link;
	std::vector<std::string> clients = { "Morgan", "Statton", "Amy" };
public:
	virtual void executeQuery(unsigned short) = 0;
	virtual void setLink(std::string) = 0;
	virtual std::string getType() = 0;
	virtual std::vector<std::string>& getClients() {
		return clients;
	}
};

class SQL : public Database {
	virtual void executeQuery(unsigned short o) {
		switch (o) {
		case 1:
			std::cout << "\n---Executed SQL SELECT---\n\n";
			break;
		case 2:
			std::cout << "\n---Executed SQL DELETE---\n\n";
			break;
		case 3:
			std::cout << "\n---Executed SQL UPDATE---\n\n";
			break;
			
		}
	}
	virtual void setLink(std::string l) {
		link = l;
	}
	virtual std::string getType() {
		return "SQL";
	}
};

class MongoDB : public Database {
	virtual void executeQuery(unsigned short o) {
		switch (o) {
		case 1:
			std::cout << "\n---Executed MongoDB SELECT---\n\n";
			break;
		case 2:
			std::cout << "\n---Executed MongoDB DELETE---\n\n";
			break;
		case 3:
			std::cout << "\n---Executed MongoDB UPDATE---\n\n";
			break;

		}
	}
	virtual void setLink(std::string l) {
		link = l;
	}
	virtual std::string getType() {
		return "MongoDB";
	}
	
};

class PC {
	Database* db;
public:
	PC(Database* db) {
		this->db = db;
	}

	void printLastClient() {
		std::cout << db->getClients()[db->getClients().size() - 1] << std::endl;
	}

	void chooseDB() {
		unsigned short opt;
		while (true) {
			std::cout << "Choose an option:\n1-SQL\n2-MongoDB\n>>>";
			std::cin >> opt;
			if (opt >= 1 && opt <= 2) break;
		}
		switch (opt) {
		case 1:
			db = new SQL();
			break;
		case 2:
			db = new MongoDB();
			break;
		};
	}

	void chooseQuery() {
		unsigned short opt;
		while (true) {
			std::cout << "Choose an option:\n1-SELECT\n2-DELETE\n3-UPDATE\n>>>";
			std::cin >> opt;
			if (opt >= 1 && opt <= 3) break;
		}
		db->executeQuery(opt);
	}

	void printType() {
		std::cout << "\n---This is a " << db->getType() << " database---\n\n";
	}
};