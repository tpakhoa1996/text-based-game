// PhanTranA2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


// TODO: 
// Make Instruction clearer
// Implement Item constructor
// Pick item and drop item
// Implement Dialog
// Implement Guessing

int main()
{
	ifstream gameConfig("gameConfig.json");
	ifstream gameHelper("gameHelper.txt");
	Game::createNewGame(gameConfig, gameHelper);
	Game::runCurrentGame();
	Game::clearGame();
    return 0;
}

