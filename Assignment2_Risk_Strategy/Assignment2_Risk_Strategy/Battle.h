#include "Country.h"
#include "Dice.h"

#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

#pragma once
class Battle
{
private:
	Country* attacker;
	Country* defender;

public:

	// constructor takes 2 pointers for countries, we will modify some attributes of the passed Country
	Battle(Country*, Country*);

	bool checkArmies();

	// here we add a parameter to attack() which represents strategy
	void attack();

	// here we pass Country by pointer
	void moveArmy(Country*, Country*, int);

	Battle();
	~Battle();
};

