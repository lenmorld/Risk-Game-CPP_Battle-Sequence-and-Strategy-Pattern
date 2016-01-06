#include <string.h>
#include <iostream>
using namespace std;

#pragma once


class Country
{
private:
	string name;
	int numArmy;
	int playerID;
	int numOfAdjacent;
	Country* adjacentCountries[10];			// holds adjacency, here we assume a country can have 10 max adjacent countries


public:

	// constructors
	Country(string, int, int);
	~Country();
	Country();

	// methods to access and modify attributes
	void decrementArmy();
	int getNumArmy();
	void setNumArmy(int);
	string getName();

	void setPlayerID(int);
	int getPlayerID();

	// methods to check and add adjacency
	bool isAdjacent(string);
	void addAdjacent(Country*);
	int getNumAdjacent();

};

