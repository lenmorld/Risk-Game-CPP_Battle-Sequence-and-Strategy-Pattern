#include "Country.h"
#include "Strategy.h"

#pragma once


class Player
{
private:
	int ID;
	string name;
	Strategy* strategy;

public:

	Player();
	Player(int, Strategy*);

	//strategy set and execute
	void setStrategy(Strategy* initStrategy);
	void executeStrategy(Country[], int);

	~Player();
};



