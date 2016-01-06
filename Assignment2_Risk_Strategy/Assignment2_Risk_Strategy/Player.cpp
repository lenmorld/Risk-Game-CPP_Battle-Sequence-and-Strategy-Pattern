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


/*
Player class - simulates a player ; Class configured with a concrete Strategy object and maintains
a reference to a Strategy object 
*/


#include "Player.h"

/*
Player constructor, plug in ID and a specific strategy to be used
*/
Player::Player(int pID, Strategy* initStrategy) {
	this->ID = pID;
	this->strategy = initStrategy;
}

/*
Modify strategy
*/
void Player::setStrategy(Strategy* newStrategy) {
	this->strategy = newStrategy;
}


/*
Method that executes a different strategy depending on what was
plugged in upon installation or set during run-time
*/
void Player::executeStrategy(Country countries[], int numOfCountries){

	this->strategy->execute(countries, numOfCountries, this->ID);
}


Player::Player()
{}


Player::~Player()
{
}
