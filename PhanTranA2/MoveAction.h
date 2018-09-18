#pragma once
#include "common.h"
#include "Action.h"
#include "Character.h"
#include "Map.h"
#include "GameHelper.h"

class MoveAction :
	public Action {
public:
	using CharacterVec = vector<Character*>;

	static MoveAction* createMoveAction(GameHelper*, helper::Direction);

	bool action();
	bool isAllowed();
	string getWarning();
	string toString();
	MoveAction* clone();
	
	~MoveAction();
private:
	MoveAction(Character*, CharacterVec*, Map*, helper::Vector);

	bool stoppedByOtherCharacter();

	Character *mainCharacter;
	CharacterVec *characterList;
	Map *map;
	helper::Vector moveVec;
};