#include "Dice.h"
#include "Battle.h"
#include <iostream>
#include <string>
using namespace std;

#pragma once

/*
Strategy Class - Abstract class, concrete strategies should inherit this and 
	provied definition for the pure virtual function execute()

	The Player Class uses this to use a concrete strategy

	****for this assignment, particularly for the Aggressive and Defensive Strategies, 
	the calculations of strategy involves calculating whether to attack or not, and if attacking, 
	the valid country to use and valid country to attack are automatically chosen based on the best advantage
	
	****this makes the strategy more meaningful and comprehensive

*/
class Strategy
{

public:
	int sID;
	string name;
	
	bool aggressiveAttack;
	bool defensiveAttack;
	int countryToUse;				
	int countryToAttack;			
	int advantage;
	bool attack ;

	// calculates difference between player armies and adjacent countries
	// this method is used by all concrete strategies
	void Calculate(Country[], int, int);

	// sets up and invokes battle after implementing the strategy to be used
	// this method is used by all concrete strategies
	void setUpBattle(Country[], int, int);

	/**
	Method whose implementation varies depending on strategy adopted
	Pure virtual function, Strategies that Extends Strategy will define this
	*/
	virtual void execute(Country[], int, int) = 0;

	Strategy();
	~Strategy();
};

/*
A concrete Strategy that implements a Aggressive Strategy
-attack if at least one country has more armies than an adjacent one
*/
class Aggressive : public Strategy {


public:

	Aggressive() {
		sID = 1;
		name = "Aggresive";
	}

	void execute(Country countries[], int numOfCountries, int playerID) {
		Calculate(countries, numOfCountries, playerID);			// calculate armies
		if (aggressiveAttack == true)
			attack = true;

		cout << "\nAGGRESSIVE Decision: ";
		(attack == true) ? cout << "ATTACK" : cout << "NOT ATTACK";
		cout << endl;

		if (attack == true)
		{
			cout << "***** Best country to use and to attack calculated ****" << endl;
			cout << "Country to Use: " << countries[countryToUse].getName() << endl;
			cout << "Country to Attack: " << countries[countryToAttack].getName() << endl;

			setUpBattle(countries, numOfCountries, playerID);		//setup and invoke battle
		}
	}

};

/*
A concrete Strategy that implements a Defensive Strategy
- attack only if all adjacent enemy countries has significantly less armies
*/
class Defensive : public Strategy {

public:

	Defensive() {
		sID = 2;
		name = "Defensive";
	}

	void execute(Country countries[], int numOfCountries, int playerID) {
		Calculate(countries, numOfCountries, playerID);					// calculate armies

		if (advantage > 2)									// siginificantly more armies
			attack = true;

		cout << "\nDEFENSIVE Decision: ";
		(attack == true) ? cout << "ATTACK" : cout << "NOT ATTACK";
		cout << endl;

		if (attack == true)
		{
			cout << "***** Best country to use and to attack calculated ****" << endl;
			cout << "Country to Use: " << countries[countryToUse].getName() << endl;
			cout << "Country to Attack: " << countries[countryToAttack].getName() << endl;

			setUpBattle(countries, numOfCountries, playerID);		//setup and invoke battle
		}

	}
};


/*
A concrete Strategy that implements a Random Strategy
-randomly choose between attacking or not, if attacking choose a random valid target
*/
class Random : public Strategy {

public:

	Random() {
		sID = 3;
		name = "Random";
	}

	void execute(Country countries[], int numOfCountries, int player) {

		Calculate(countries, numOfCountries, player);

		// first we get random value
		Dice d1;
		int random = d1.getRandomValue();

		// dice roll 456 true, 123 false
		attack = (random > 3) ? true : false;

		cout << "\nRandom Decision: " ;
		(attack == true) ? cout << "ATTACK" : cout << "NOT ATTACK";
		cout << endl;
		
		if (attack)
		{
			int *attackCandidates = new int[];			//int array
			int ctr1 = 0;

			//loop through all countries owned by player which has > 1 armies
			for (int i = 0; i < numOfCountries; i++) {

				if ((countries[i].getPlayerID() == player) && (countries[i].getNumArmy() > 1))
				{
					//get country index and add to array
					attackCandidates[ctr1] = i;
					ctr1++;
				}
			}

			cout << "\nYou have " << ctr1 << " countries available for battle " << endl;

			if (ctr1 == 0)
			{
				cout << "\nNo more countries available for battle" << endl;
				return;
			}

			//now we generate a random number from start and end index of the array
			int attackerCandidateIndex = Dice::randomize(0, ctr1);

			//we get the country index represented in the candidates index, and set it as attacker
			countryToUse = attackCandidates[attackerCandidateIndex];
			//cout << "Random country: " << countries[countryToUse].getName() << endl;

			//------ adjacent countries of country -----
			int *defendCandidates = new int[];			//int array
			int ctr2 = 0;
			//loop through all the adjacent countries of the  randomly chosen country
			for (int i = 0; i < numOfCountries; i++)
			{
				if (countries[countryToUse].isAdjacent(countries[i].getName()) && countries[i].getPlayerID() != player)
				{
					//cout << countries[i].getName() << countries[i].getNumArmy() << endl;


					//get country index and add to array
					defendCandidates[ctr2] = i;
					ctr2++;

					//cout << ctr2;
				}
			}

			cout << "There are " << ctr2 << " adjacent countries to attack " << endl;

			if (ctr2 == 0)
			{
				cout << "\nNo adjacent countries available for battle" << endl;
				return;
			}

			//now we generate a random number from start and end index of the array
			int defenderCandidateIndex = Dice::randomize(0, ctr2);

			//we get the country index represented in the candidates index, and set it as attacker
			countryToAttack = defendCandidates[defenderCandidateIndex];

			cout << "\nRandom country for battle: " << countries[countryToUse].getName() << endl;
			cout << "Random country to attack: " << countries[countryToAttack].getName() << endl;
			setUpBattle(countries, numOfCountries, player);		//setup and invoke battle
		}
			
	}// end of execute

};


/*
A concrete Strategy that implements a Normal Strategy
-manual / complete user control over all stage of the battle
*/
class Normal : public Strategy {

public:

	Normal() {
		sID = 4;
		name = "Normal";

	}

	void execute(Country countries[], int numOfCountries, int player) {

		Calculate(countries, numOfCountries, player);

		char charAttack;
		do {
			cout << "\nDo you want to Attack? (1 for YES, 0 for NO) : _ ";
			cin >> charAttack;
		} while (charAttack < '0' || charAttack > '1');

		attack = (charAttack == '1') ? true : false;

		if (attack)
		{

			// #1#  The player chooses one of the countries he owns
			cout << " Choose country to launch attack from:_ " << endl;

			int countryChoiceAttack = -1;

			// prompt user until valid input
			do {
				cout << "Enter choice here (-1 to exit): _  ";
				cin >> countryChoiceAttack;

				if (countryChoiceAttack == -1)			//if user wants to exit
					return;
				//BattleDriver::forceExit();

			} while (countryChoiceAttack < 0 || countries[countryChoiceAttack].getPlayerID() != player);			// loop if not player 1

			getchar();	// get extra input

			// # 2 #  Declares an attack on an adjacent country that is owned by another player
			cout << "\nChoose adjacent country to attack: \n" << endl;

			// print all adjacent countries
			for (int i = 0; i < numOfCountries; i++)
			{
				if (countries[countryChoiceAttack].isAdjacent(countries[i].getName()) && countries[i].getPlayerID() != player)
					cout << (i) << "_" << countries[i].getName() << " with " << countries[i].getNumArmy() << " armies " << endl;
			}

			int countryChoiceDefend = -1;

			//prompt user until valid input of adjacent country
			do {
				cout << "\nEnter choice here (-1 to exit): _ ";
				cin >> countryChoiceDefend;

				if (countryChoiceDefend == -1)
					return;

			} while (countryChoiceDefend < 0 || !countries[countryChoiceAttack].isAdjacent(countries[countryChoiceDefend].getName())
				|| countries[countryChoiceDefend].getPlayerID() == player);

			// use attacking and defending countries chosen by user
			countryToUse = countryChoiceAttack;
			countryToAttack = countryChoiceDefend;

			setUpBattle(countries, numOfCountries, player);		//setup and invoke battle
		}


	}// end of execute

};



