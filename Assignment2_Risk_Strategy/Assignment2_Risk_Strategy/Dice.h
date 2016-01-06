#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <chrono>			// used for creating delay
#include <thread>			// used for creating delay

#pragma once

class Dice
{
private:
	int value;

public:
	Dice();
	int getRandomValue();
	~Dice();

	static int max(Dice *, int);		// static methods gets max of a Dice array
	static int max2(Dice *, int);		// 2nd max

	static int randomize(int, int);		// static method to give back a random number given a range


};

