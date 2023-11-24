#pragma once
#include <iostream>
#include <vector>

typedef unsigned int uint;

class Weapon {
	uint baseDamage;
	float attackSpeed;
public:
	void setBaseDamage(uint dam) {
		baseDamage = dam;
	}

	uint getBaseDamage() {
		return baseDamage;
	}

	void setAttackSpeed(float as) {
		attackSpeed = as;
	}

	float getAttackSpeed() {
		return attackSpeed;
	}

	virtual void attack() = 0;
	virtual void powerAttack() = 0;
};

class Sword : public Weapon {
public:
	Sword() {
		setBaseDamage(25);
		setAttackSpeed(1.75);
	}

	virtual void attack() {
		std::cout << "Sword attacks for " << getBaseDamage() << " hitpoints with " << getAttackSpeed()
			<< " attacks per second\n";
	}

	virtual void powerAttack() {
		std::cout << "Sword power attacks for " << getBaseDamage() * 2 / 1.15 << " hitpoints with " <<
			getAttackSpeed() << " attacks per second\n";
	}
};

class Axe : public Weapon {
public:
	Axe() {
		setBaseDamage(35);
		setAttackSpeed(.85);
	}

	virtual void attack() {
		std::cout << "Axe attacks for " << getBaseDamage() << " hitpoints with " << getAttackSpeed() << 
			" attacks per second\n";
	}

	virtual void powerAttack() {
		std::cout << "Axe power attacks for " << getBaseDamage() * 1.85 << " hitpoints with " << 
			getAttackSpeed() << " attacks per second\n";
	}
};

class Enchant : public Weapon {
protected:
	Weapon* weapon;

public:
	Enchant(Weapon* w, uint dam, float as) : weapon(w) {
		weapon->setBaseDamage(weapon->getBaseDamage() + dam);
		weapon->setAttackSpeed(weapon->getAttackSpeed() + as);
	}

	virtual void setBaseDamage(uint dam) {
		weapon->setBaseDamage(dam);
	}

	virtual void setAttackSpeed(float as) {
		weapon->setAttackSpeed(as);
	}

	virtual void attack() {
		weapon->attack();
	}

	virtual void powerAttack() {
		weapon->powerAttack();
	}
};

class FireEnchant : public Enchant {
public:
	FireEnchant(Weapon* w) : Enchant(w, 15, 0) {
	}

	virtual void attack() {
		Enchant::attack();
		std::cout << "Additional damage from Fire Enchant: 15 hitpoints\n";
	}

	virtual void powerAttack() {
		Enchant::powerAttack();
		std::cout << "Additional damage from Fire Enchant: 15 hitpoints & 3 hitpoints/sec over 10 seconds\n";
	}
};

class WindEnchant : public Enchant {
public:
	WindEnchant(Weapon* w) : Enchant(w, 7, 1.15) {
	}

	virtual void attack() {
		Enchant::attack();
		std::cout << "Additional damage from Wind Enchant: 7 hitpoints\n";
	}

	virtual void powerAttack() {
		Enchant::powerAttack();
		std::cout << "Additional damage from Wind Enchant: 7 hitpoints & increased attack speed + 1.15\n";
	}
};
