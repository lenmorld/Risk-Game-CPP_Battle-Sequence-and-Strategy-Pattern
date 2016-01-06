/*
COMP 345_ Individual Assignment 2

Risk Game
Battle + Player Strategy Pattern

DESIGN:

6 classes are implemented
- Battle	: contains all methods to simulate the battle phase, including attack
- Country	: simulates the Countries and their attributes including name, num of armies and adjacent countries
- Dice		: simulates a dice object, which generates random numbers 1 to 6, and some other needed random numbers
- BattleDriver	:	creates countries and adjacencies, calls battle and shows the initiation and results of each battle,
also provides an initial menu for the battle phase

*** updates for assignment 2 ****
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
BattleDriver class - holds everything together, contains implementations of methods for the battle of attacker and defender

creates countries and adjacencies, provides an initial menu for which Player's turn it is, and choice of strategy that will invoke battle

here we hardcoded the number of countries, Countries and set their adjacencies by calling some methods in the Country class
to focus on the Strategy Selection and the Battle Phase
*/

#include "BattleDriver.h"

int main() {

	cout << "############# RISK GAME BATTLE PHASE ################" << endl;


	//################# HARD-CODED COUNTRIES and ADJACENCIES ###########################
	// Countries, country names and adjacencies must be implemented from the Map,
	// but is simulated here by hard-coding
	// A Country array is created, each country with
	//	- country name
	//	- array of adjacent countries
	//	- player ID that owns this country
	//* adjacencies are defined two-way, that is, if Canada and USA are adjacent,
	//* Canada is in USA's adjacency array, and USA is in Canada's adjacency array
	/*
		a player array is also created, assuming there are 4 players
		and the rotation is semi-simulated by prompting whose turn it is
		*/

	int numOfCountries = 12;

	//create array of countries
	Country countries[12];

	//COUNTRIES owned by Player - available for attack
	// name, number or armies, Player ID
	countries[0] = Country("Canada", 11, 1);
	countries[1] = Country("Afghanistan", 5, 1);
	countries[2] = Country("Madagascar", 4, 1);
	countries[3] = Country("China", 3, 1);

	//COUNTRIES owned by other players - defending
	// name, number or armies, Player ID	
	countries[4] = Country("Greenland", 8, 2);		// belongs Player2
	countries[5] = Country("USA", 7, 3);			// belongs to Player 3

	countries[0].addAdjacent(&countries[4]);		// add Greenland as adjacency to Canada
	countries[0].addAdjacent(&countries[5]);		// add USA as adjacency to Canada

	countries[4].addAdjacent(&countries[0]);		// add Canada as adjacency to USA
	countries[5].addAdjacent(&countries[0]);		// add Canada as adjacency to USA

	countries[6] = Country("Russia", 3, 3);					// adjacencies of Afghanistan
	countries[7] = Country("Middle East", 8, 4);

	countries[1].addAdjacent(&countries[6]);
	countries[1].addAdjacent(&countries[7]);

	countries[6].addAdjacent(&countries[1]);
	countries[7].addAdjacent(&countries[1]);

	countries[8] = Country("S. Africa", 2, 2);					// adjacencies of Madagascar		
	countries[9] = Country("E. Africa", 6, 4);

	countries[2].addAdjacent(&countries[8]);
	countries[2].addAdjacent(&countries[9]);

	countries[8].addAdjacent(&countries[2]);
	countries[9].addAdjacent(&countries[2]);

	countries[10] = Country("India", 1, 3);					// adjacencies of China	
	countries[11] = Country("Mongolia", 6, 4);

	countries[3].addAdjacent(&countries[10]);
	countries[3].addAdjacent(&countries[11]);

	countries[10].addAdjacent(&countries[3]);
	countries[11].addAdjacent(&countries[3]);


	//Player array

	int numOfPlayers = 4;

	//create array of players
	Player players[5];			// extra 1 to make it a 1-based array

	//create all players, with player ID, initialize to Normal strategy
	players[1] = Player(1, new Normal());
	players[2] = Player(2, new Normal());
	players[3] = Player(3, new Normal());
	players[4] = Player(4, new Normal());

	bool nextPlayerUp = false;

	do				// main menu loop
	{

		//#################### PICK PLAYER #################################################
		// normally this would be decided by the game driver, but here we simulate
		// by providing a prompt whose turn it is
		// 4 players - 1 2 3 4

		cout << "Whose turn is it? Player: (1 2 3 4) _" << endl;
		int player = -1;
		// prompt user until valid input
		do {
			cout << "Enter choice here (-1 to exit): _  ";
			cin >> player;
			if (player == -1)			//if user wants to exit
				BattleDriver::forceExit();
		} while (player < 1 || player > 4);		// loop until correct player number


		// create chosen player, with player ID, initialize to Normal strategy
		players[player] = Player(player, new Normal());


		bool battleAgain = false;

		do {

			/* ############# PICK STRATEGY  #######################*/

			cout << " Choose a strategy pattern (1 2 3 4):_ " << endl
				<< "[1] Aggressive (Attack once there is an advantage over ONE adjacent country) " <<
				"\n[2] Defensive (Attack only if there is an advantage over ALL adjacent country)" <<
				"\n[3] Random\n[4] Normal (Manual)\n";

			int strategy = -1;

			// prompt user until valid input
			do {
				cout << "Enter choice here : _  ";
				cin >> strategy;
			} while (strategy < 1 || strategy > 4);

			// set player's strategy to chosen one
			switch (strategy)  {
			case 1:  players[player].setStrategy(new Aggressive());  	break;
			case 2:  players[player].setStrategy(new Defensive());	break;
			case 3:	 players[player].setStrategy(new Random());		break;
			default:  players[player].setStrategy(new Normal());		break;
			}


			//#########################################################
			// print all countries owned by Player# and their adjacencies

			cout << "\n\n#############################################\nPLAYER " << player << "'s TURN - BATTLE Phase  \n#############################################\n" << endl;
			cout << "   COUNTRY___________ARMIES_________ADJACENT______ARMIES________OWNED BY" << endl;
			cout << "---------------------------------------------------------------" << endl;

			for (int i = 0; i < numOfCountries; i++)
			{	//get all countries owned by player 
				if (countries[i].getPlayerID() == player)
				{
					cout << "   " << "(" << i << ")" << setw(17) << left << countries[i].getName() << setw(15) << left << countries[i].getNumArmy() << endl;
					for (int j = 0; j < numOfCountries; j++)
					{	// if adjacent and if not owned by other players
						if (countries[i].isAdjacent(countries[j].getName()) && countries[j].getPlayerID() != player)
							cout << setw(37) << right << "   " << "(" << j << ")" << setw(13) << left << countries[j].getName() << setw(5) << left << countries[j].getNumArmy() << setw(8) << left << "Player" << countries[j].getPlayerID() << endl;
					}
					cout << "-------------------------------------------------------------\n" << endl;
				}
			}

			//################# STRATEGY PATTERN execution #################
			players[player].executeStrategy(countries, numOfCountries);			// need to pass country array and length
			//executeStrategy also invokes battle()

			//############# END OF CURRENT BATTLE #####################
			char charBattle;
			do {
				cout << "Player " << player << ", Do you want to continue in Battle Phase? (1 for YES, 0 for NO) : _ ";
				cin >> charBattle;
			} while (charBattle < '0' || charBattle > '1');

			battleAgain = (charBattle == '1') ? true : false;

		} while (battleAgain == true);			// keep looping if user wants to continue on Battle Phase


		char nextPlayer;
		do {
			cout << "\nNext Player's Turn? (1 for YES, 0 TO EXIT GAME) : _ ";
			cin >> nextPlayer;
		} while (nextPlayer < '0' || nextPlayer > '1');

		nextPlayerUp = (nextPlayer == '1') ? true : false;


	} while (nextPlayerUp);

	cout << "\n##### Thank you for playing. #########\n" << endl;
	system("pause");
	return 0;

}		// end main


void BattleDriver::forceExit() {
	cout << "\n##### Thank you for playing. #########\n" << endl;
	system("pause");
	exit(EXIT_SUCCESS);
}

BattleDriver::BattleDriver()
{
}


BattleDriver::~BattleDriver()
{
}