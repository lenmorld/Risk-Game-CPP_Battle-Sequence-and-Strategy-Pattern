/*
COMP 345_ Individual Assignment 1

Battle_Risk Game

Simulate the Battle phase of the game


DESIGN:

4 classes are implemented
- Battle	: contains all methods to simulate the battle phase, including attack
- Country	: simulates the Countries and their attributes including name, num of armies and adjacent countries
- Dice		: simulates a dice object, which generates random numbers 1 to 6
- BattleDriver	:	creates countries and adjacencies, calls battle and shows the initiation and results of each battle,
also provides an initial menu for the battle phase


*/


/*
Dice class - simulates the dice object that generates random numbers and keeps them for later use
*/


#include "Dice.h"

Dice::Dice(){
	// srand() to seed the randomizer based on a value that is always changing - current time
	srand(time(NULL));
}

int Dice::getRandomValue() {

	// provided delay for random generator
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	rand();

	// generate a random number from 1 to 6 (inclusive)
	int iRandom = rand() % 6 + 1;
	value = iRandom;
	return value;
}


// gets MAX dice value
//this accepts an array of Dice, passed by pointer
int Dice::max(Dice * d, int num) {
	int maxValue = 0;

	for (int i = 0; i < num; i++){

		if (d[i].value > maxValue)
			maxValue = d[i].value;
	}
	return maxValue;
}

//gets 2nd Max value
//this accepts an array of Dice, passed by pointer
int Dice::max2(Dice * d, int num) {
	int maxValue = 0;
	int maxIndex = 0;

	//get max
	for (int i = 0; i < num; i++){
		if (d[i].value > maxValue)
		{
			maxValue = d[i].value;
			maxIndex = i;		// get index of max
		}
	}

	//set value of max dice to 0, to allow getting the second max after
	d[maxIndex].value = 0;
	maxValue = 0;		//reset max

	// get 2nd max
	for (int i = 0; i < num; i++){
		if (d[i].value > maxValue)
			maxValue = d[i].value;
	}

	return maxValue;
}

// generate random number given a range
int Dice::randomize(int start, int end) {

	srand(time(NULL));
	rand();			// generate random number using seed

	// calibrate to fit range, given start to end (inclusive)
	int iRandom = rand() % end + start;

	return iRandom;

}

Dice::~Dice()
{
}
