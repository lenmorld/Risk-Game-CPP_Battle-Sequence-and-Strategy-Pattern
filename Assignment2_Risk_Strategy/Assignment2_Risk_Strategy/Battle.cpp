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
Battle Phase Rules used

Rules followed are from the Assignment 1 handout, with the addition of consulting  http://www.hasbro.com/common/instruct/risk.pdf.

1.  The player chooses one of the countries he owns with >= 2 armies,
2.  Declares an attack on an adjacent country that is owned by another player.
3. A battle is then simulated by the attacker choosing to roll at most 3 dice, and the defender choosing to roll at most 2 dice .
A document from Hasbro Risk is consulted, http://www.hasbro.com/common/instruct/risk.pdf
regarding the choice of number of dices for attacker and defender.
It says in the document, page 9
"You, the attacker, will roll 1,2 or 3  dice: You must have at least one
more army in your territory than the number of dice you roll.
The defender will roll either 1 or 2  dice: To roll 2 dice, he or she
must have at least 2 armies on the territory under attack. "
4. Best dice rolls are compared between attacker and defender. If the next dice roll of attacker <= defender,
attacker loses one army(dice). If attacker > defender, defender loses one army(dice).
5. If the defender rolled two dice then the 2nd best dice are compared, as in (4)
6. The attacker can choose to continue attacking until either all his armies or all the defending armies
have been eliminated.
7. If all the defender's armies are eliminated the attacker captures the territory.
8. The attacking player must place a number of armies in the conquered country which >= dice used in attack that resulted in conquering the country.
9. There must be an “all-in” attack mode that uses the maximum number of dice on both sides and runs automatically until the attack results in either
a) The defending country to be conquered and all armies of the conquering country are moved to the conquered country
or b) the attacking country runs out of armies and cannot attack anymore.

Rules followed are from the Assignment 1 handout, with the addition of consulting  http://www.hasbro.com/common/instruct/risk.pdf.
*/


/*
Battle class - contains implementations of methods for the battle of attacker and defender
*/


#include "Battle.h"


// constructor
Battle::Battle(Country* attackCountry, Country* defendCountry) {

	attacker = attackCountry;			// get pointer to attacker and defender countries
	defender = defendCountry;
}

/*check number of armies if valid before start battle*/
bool Battle::checkArmies() {

	if (attacker->getNumArmy() > 1 && defender->getNumArmy() > 0)
		return true;
	else
	{
		if (attacker->getNumArmy() == 1)
			cout << "cannot attack with 1 army, must leave 1 army in this country: " << attacker->getName() << endl;

		cout << "!!! Cannot launch attack\n"
			<< "Not enough armies on attacker/defender side\n" << endl;
		return false;
	}
}

// this countains the whole attack sequence
void Battle::attack() {

	bool allIn = false;

	int unitBattleAttacker = 0, unitBattleDefender = 0;		// init variables
	int maxUnitAttacker = 3, maxUnitDefender = 2;

	cout << "Attacker: P " << attacker->getPlayerID() << " " << attacker->getName() << "-" << attacker->getNumArmy() << " units " << endl;
	cout << "Defender: P " << defender->getPlayerID() << " " << defender->getName() << "-" << defender->getNumArmy() << " units " << endl;

	char charAllIn;
	do {
		cout << "\n Do you want to go all in? (1 for YES, 0 for NO) : _ ";
		cin >> charAllIn;
	} while (charAllIn < '0' || charAllIn > '1');

	allIn = (charAllIn == '1') ? true : false;

	// facilitate infinite loop, breaking out will depend on battle results
	while (true)
	{
		unitBattleAttacker = 0, unitBattleDefender = 0;

		cout << "\nAttacker: P " << attacker->getPlayerID() << " " << attacker->getName() << "-" << attacker->getNumArmy() << " units " << endl;
		cout << "Defender: P " << defender->getPlayerID() << " " << defender->getName() << "-" << defender->getNumArmy() << " units " << endl;

		//## 3. attacker choosing to roll at most 3 dice, and the defender choosing to roll at most 2 dice . ##
		if (!allIn) {			// if not all-in, let attacker and defender choose number of armies(dice) to use
			do {
				cout << "\nHow many armies do the attacker want to use? ";

				if (attacker->getNumArmy() > 3)
				{
					maxUnitAttacker = 3;
					cout << " (3 2 1) " << endl;
				}
				else if (attacker->getNumArmy() == 3)
				{
					maxUnitAttacker = 2;
					cout << " (2 1) " << endl;
				}
				else if (attacker->getNumArmy() == 2)
				{
					maxUnitAttacker = 1;
					cout << " (1) " << endl;
				}

				cin >> unitBattleAttacker;

			} while (unitBattleAttacker <= 0 || unitBattleAttacker > maxUnitAttacker);

			getchar();

			do {
				cout << "\nHow many armies do the defender want to use? ";

				if (defender->getNumArmy() >= 2)		// 2 or more
				{
					maxUnitDefender = 2;
					cout << " (2 1) " << endl;
				}
				else if (defender->getNumArmy() == 1)
				{
					maxUnitDefender = 1;
					cout << " (1) " << endl;
				}

				cin >> unitBattleDefender;

			} while (unitBattleDefender <= 0 || unitBattleDefender > maxUnitDefender);

			getchar();

		}
		else {	// allIn	# 9 all-in mode #			go max (3 for attacker, 2 for defender)
			if (attacker->getNumArmy() > 3)
				unitBattleAttacker = 3;
			else if (attacker->getNumArmy() == 3)
				unitBattleAttacker = 2;
			else if (attacker->getNumArmy() == 2)
				unitBattleAttacker = 1;

			if (defender->getNumArmy() >= 2)
				unitBattleDefender = 2;
			else if (defender->getNumArmy() == 1)
				unitBattleDefender = 1;

		}


		cout << "    Attack: " << unitBattleAttacker << " vs  Defend: " << unitBattleDefender << endl;

		//prepare dices to use, make an array of dices for attacking and defending countries
		Dice *dAttacker = new Dice[unitBattleAttacker];
		Dice *dDefender = new Dice[unitBattleDefender];

		cout << "    Attacker dices: ";
		//roll dices of attacker
		for (int i = 0; i < unitBattleAttacker; i++)
			cout << "       " << dAttacker[i].getRandomValue() << " ";
		cout << endl;
		cout << "    Defender dices: ";
		//roll dices of defender
		for (int i = 0; i < unitBattleDefender; i++)
			cout << "       " << dDefender[i].getRandomValue() << " ";

		cout << endl;


		//# 4 # Best dice rolls are compared between attacker and defender.

		int attackMax = Dice::max(dAttacker, unitBattleAttacker);
		int defendMax = Dice::max(dDefender, unitBattleDefender);

		if (attackMax <= defendMax)
		{
			// defender wins, attacker must lose an army(dice)
			cout << "------> " << defender->getName() << "(defender) wins, " << " [" << defendMax << " vs " << attackMax << "], "
				<< attacker->getName() << " loses an army" << endl;
			attacker->decrementArmy();
		}
		else
		{
			// attacker wins, defender must lose an army (dice)
			cout << "-------> " << attacker->getName() << "(attacker) wins, " << " [" << attackMax << " vs " << defendMax << "], "
				<< defender->getName() << " loses an army" << endl;
			defender->decrementArmy();
		}

		// # 5 # If the defender rolled two dice then the 2nd best dice are compared, as in (4)
		if (unitBattleDefender == 2 && unitBattleAttacker > 1)
		{
			//#### 2nd DICE COMPARE

			//get 2nd max
			int attackMax2 = Dice::max2(dAttacker, unitBattleAttacker);
			int defendMax2 = Dice::max2(dDefender, unitBattleDefender);

			if (attackMax2 <= defendMax2)
			{
				// defender wins, attacker must lose an army(dice)
				cout << "------> 2nd : " << defender->getName() << "(defender) wins, " << " [" << defendMax2 << " vs " << attackMax2 << "], "
					<< attacker->getName() << " loses an army" << endl;
				attacker->decrementArmy();
			}
			else
			{
				// attacker wins, defender must lose an army (dice)
				cout << "-------> 2nd : " << attacker->getName() << "(attacker) wins, " << " [" << attackMax2 << " vs " << defendMax2 << "], "
					<< defender->getName() << " loses an army" << endl;
				defender->decrementArmy();
			}
		}

		//### END of ATTACK round ###

		// # 6 # if defender has no more army and attacker has more
		if (defender->getNumArmy() == 0 && attacker->getNumArmy() > 0)
		{
			cout << "\n ### Attacker " << attacker->getName() << " defeated all armies of Defender " << defender->getName() << "  #### " << endl;

			//  # 7 # If all the defender's armies are eliminated the attacker captures the territory.

			//attacker won, he must place armies >= unitBattleAtacker
			int numArmyTransfer = 0;

			// move armies if unit used is not equal to number of armies
			if (unitBattleAttacker != attacker->getNumArmy())
			{
				if (allIn)	// # 9a #  all armies of the conquering country are moved to the conquered country
				{
					numArmyTransfer = attacker->getNumArmy() - 1;			// move all, just leave one behind 
				}
				else
				{
					//prompt user how many armies to move?
					if (unitBattleAttacker == (attacker->getNumArmy() - 1))
						cout << "\nYou can move armies, (" << unitBattleAttacker << ")" << endl;
					else
						cout << "\nYou can move armies, (" << unitBattleAttacker << " - " << (attacker->getNumArmy() - 1) << ")" << endl;

					// # 8 # The attacking player must place a number of armies in the conquered country 
					// which >= dice used in attack that resulted in conquering the country.

					// make sure number of armies transferred is >= number of armies used, and less than number of armies (need to leave at least one behind)
					while (numArmyTransfer < unitBattleAttacker || numArmyTransfer >= attacker->getNumArmy()) {
						cout << "How many armies do you want to move to " << defender->getName() << ") _" << endl;
						cin >> numArmyTransfer;
					}

					getchar();		// get extra input
				}


				// call method to move armies
				Battle::moveArmy(attacker, defender, numArmyTransfer);
			}
			break;

		}		// # 6 # if attacker has only 1 left
		else if (attacker->getNumArmy() <= 1)
		{
			cout << "\n!!! Cannot attack with 1 army, must leave 1 army in this country: " << attacker->getName() << endl;
			cout << "!!!Attacker has no more armies for attack" << endl;
			break;
		}

		if (allIn == false) {

			cout << "\nAttacker: P " << attacker->getPlayerID() << " " << attacker->getName() << "-" << attacker->getNumArmy() << " units " << endl;
			cout << "Defender: P " << defender->getPlayerID() << " " << defender->getName() << "-" << defender->getNumArmy() << " units " << endl;

			char charContinue;
			do {
				cout << "\n Do you want to continue attacking? (1 for YES, 0 for NO) : _ ";
				cin >> charContinue;
			} while (charContinue < '0' || charContinue > '1');

			//allIn = (charContinue == '1') ? true : false;

			if (charContinue != '1')
				break;


		}

	}	// end while

	cout << "\n############## Attack finished ###################" << endl;

}

//method that moves armies from attacking country to defending country
void Battle::moveArmy(Country* cAttack, Country* cDefend, int numArmyTransfer) {

	cDefend->setPlayerID(cAttack->getPlayerID());							// change ownership of country to attacking country
	cAttack->setNumArmy(cAttack->getNumArmy() - numArmyTransfer);			// transfer armies to the defend country
	cDefend->setNumArmy(numArmyTransfer);
}

Battle::~Battle()
{
}
