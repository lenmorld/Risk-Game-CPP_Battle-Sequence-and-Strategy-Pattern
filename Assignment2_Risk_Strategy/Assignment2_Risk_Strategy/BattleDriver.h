#include "Country.h"
#include "Battle.h"
#include "Strategy.h"
#include "Player.h"

#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

#pragma once
class BattleDriver
{
public:
	BattleDriver();
	~BattleDriver();
	static void forceExit();
};

