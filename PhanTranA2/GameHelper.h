#pragma once
#include "Character.h"
#include "Map.h"
#include "ControlUnit.h"
#include "Guess.h"

class GameHelper {
	friend class Game;
public:
	using CharacterVec = vector<Character*>;
	using ControlStack = stack<ControlUnit*>;
	using RoleVec = vector<Role*>;
	
	void pushOneControlUnit(ControlUnit*);

	bool goBackOneControlUnit();

	Map* getMap();
	CharacterVec* getCharacterList();
	Investigator* getMainCharacter();
	string getInstruction();
	Guess* getGuess();

private:
	Map *map = nullptr;
	CharacterVec* characterList = nullptr;
	Investigator* mainCharacter = nullptr;
	ControlStack* controlStack = nullptr;
	Guess* guess = nullptr;
	string instruction;
	RoleVec roles;
	
	GameHelper();
	~GameHelper();
};