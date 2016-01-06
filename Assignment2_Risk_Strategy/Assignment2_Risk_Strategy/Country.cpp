/*
COMP 345_ Individual Assignment 2

Risk Game
Battle + Player Strategy Pattern

DESIGN:

6 classes are implemented
- Battle	: contains all methods to simulate the battle phase, including attack
- Country	: simulates the Countries and their attributes including name, num of armies and adjacent countries
- Dice		: simulates a dice object, which generates random numbers 1 to 6
- BattleDriver	:	creates countries and adjacencies, calls battle and shows the initiation and results of each battle,
also provides an initial menu for the battle phase

*** updates for assignment 2
- Player : simulates the player, with a strategy pattern
- Strategy: uses Strategy Pattern

Rules followed are from the Assignment 1 handout, with the addition of consulting  http://www.hasbro.com/common/instruct/risk.pdf.
Please see Assignment2.docx for details

############### STRATEGY PATTERN ###########

Strategy pattern allows to change the behavior / decision-making strategy
based on some conditions that are only to be determined at runtime,
such as user input (prompt user for a strategy),
battle results (number of countries left after a battle), etc.

Using Strategy Pattern allows us to implement a specific algorithm
wihtout affecting the Player objects that uses it

############################################
*/


#include "Country.h"

//default constructor
Country::Country()
{
	name = "";
	numArmy = 0;
	numOfAdjacent = 0;
}

//parameterized constructor
Country::Country(string n, int a, int p)
{
	name = n;
	numArmy = a;
	playerID = p;
	numOfAdjacent = 0;
}


//## some mutator and accessor methods ##

int Country::getNumArmy() {
	return numArmy;
}

void Country::setNumArmy(int n) {
	numArmy = n;
}

//accepts a pointer to Country, adds to adjacency array of this current Country
void Country::addAdjacent(Country* c) {
	this->adjacentCountries[numOfAdjacent] = c;
	numOfAdjacent++;				// increment adjacent countries
}

int Country::getNumAdjacent() {
	return numOfAdjacent;
}

//checks if passed country name is adjacent, we assume no duplicate of country names
bool Country::isAdjacent(string cName) {

	for (int i = 0; i < numOfAdjacent; i++) {
		if (cName == adjacentCountries[i]->getName())
			return true;
	}
	return false;
}

string Country::getName() {
	return name;
}

void Country::decrementArmy() {
	if (numArmy > 0)
		numArmy--;
}

void Country::setPlayerID(int p) {
	playerID = p;
}

int  Country::getPlayerID() {
	return playerID;
}


Country::~Country()
{

}
