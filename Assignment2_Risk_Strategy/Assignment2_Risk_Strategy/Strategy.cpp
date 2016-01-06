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


#include "Strategy.h"

// calculates difference between player armies and adjacent countries - otherwords, ADVANTAGE
// this method is used by all concrete strategies
void Strategy::Calculate(Country countries[], int numOfCountries, int playerID)
{

	// itialize all variables
	aggressiveAttack = false;
	countryToUse = -1;
	countryToAttack = -1;
	advantage = 0;
	attack = false;


	//check each country owned by attacker if it has more armies than an adjacent country
	for (int i = 0; i < numOfCountries; i++)
	{
		//get all countries owned by player 
		if (countries[i].getPlayerID() == playerID)
		{
			for (int j = 0; j < numOfCountries; j++)
			{	// if adjacent and if not owned by current player
				if (countries[i].isAdjacent(countries[j].getName()) && countries[j].getPlayerID() != playerID)
				{
					int tempA = countries[i].getNumArmy() - countries[j].getNumArmy();		// calculate difference between num. of armies

					//cout << "advantage level: " << tempA << endl;

					if (tempA > advantage)				// if there's more advantage than last pair of countries
					{
						aggressiveAttack = true;		// set to true if there is at least one
						advantage = tempA;
						countryToUse = i;
						countryToAttack = j;
					}
				}
			}
		}

	}

}


// sets up and invokes battle after implementing the strategy to be used
// this method is used by all concrete strategies
void Strategy::setUpBattle(Country countries[], int numOfCountries, int player)
{

	// ################# SET-UP BATTLE and CALL ###############

	//make pointers for attacking and defending countries
	Country* cAttack = &countries[countryToUse];
	Country* cDefend = &countries[countryToAttack];

	Battle b1(cAttack, cDefend);			// create battle, passing 2 countries

	if (attack == true) {		// if player decides to attack

		if (b1.checkArmies())		// check number of armies first
		{
			cout << "\n### LAUNCHING attack from " << cAttack->getName() << " to " << cDefend->getName() << " ###\n" << endl;

			b1.attack();		// start attack, pass strategy used as argument

			cout << "\nUPDATES:\n";
			cout << "Countries owned by Player: " << player << endl;
			cout << "   COUNTRY___________ARMIES_________ADJACENT______ARMIES________OWNED BY" << endl;

			cout << "---------------------------------------------------------------" << endl;

			for (int i = 0; i < numOfCountries; i++)
			{
				//get all countries owned by player 
				if (countries[i].getPlayerID() == player)
				{
					cout << "   " << "(" << i << ")" << setw(17) << left << countries[i].getName() << setw(15) << left << countries[i].getNumArmy() << endl;
					for (int j = 0; j < numOfCountries; j++)
					{	// if adjacent and if not owned by other players
						if (countries[i].isAdjacent(countries[j].getName()) && countries[j].getPlayerID() != player)
							cout << setw(37) << right << "   " << "(" << j << ")" << setw(13) << left << countries[j].getName() << setw(5) << left << countries[j].getNumArmy() << setw(8) << left << "Player" << countries[j].getPlayerID() << endl;
					}
					cout << "-------------------------------------------------------------" << endl;
				}
			}
		}

	}

}


Strategy::Strategy()
{

}


Strategy::~Strategy()
{

}
