#pragma once
#include "Map.h"
#include "Character.h"
#include "Investigator.h"
#include "Suspect.h"
#include "common.h"
#include "GameHelper.h"

class Game {
public:
	static void createNewGame(istream&, istream&);
	static bool runCurrentGame();
	static void clearGame();

	void run();

private:
	Game(istream&, istream&);
	~Game();

	GameHelper* helper = nullptr;

	static Game* currentGame;

	string introduction;

	void initGameConfig(JSON*);
	void initGameHelper(istream&);

	void intro();
	void loop();
	void end();

	void getPlayerInfo();
};