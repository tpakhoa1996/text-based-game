#include "stdafx.h"
#include "MoveAction.h"


MoveAction::MoveAction(
	Character* mainCharacter, 
	CharacterVec* characterList, 
	Map* map,
	helper::Vector moveVec
) 
	: 
	Action(new Time(1)), 
	mainCharacter(mainCharacter), 
	characterList(characterList),
	map(map),
	moveVec(moveVec)
{}

bool MoveAction::stoppedByOtherCharacter() {
	bool check = false;
	helper::Point nextPosition = mainCharacter->getNextPosition(moveVec);
	for (auto character : *characterList) {
		if (nextPosition == character->getPosition()) {
			check = true;
			break;
		}
	}

	return check;
}

bool MoveAction::isAllowed() {
	bool check = false;
	helper::Point nextPosition = mainCharacter->getNextPosition(moveVec);
	if (checkTimeLimit() &&
		!map->checkPointOutsideMap(nextPosition) &&
		!map->checkPointOnBorder(nextPosition) &&
		!stoppedByOtherCharacter()) {
		check = true;
	}
	return check;
}

string MoveAction::getWarning() {
	ostringstream out;
	out << "Your move is invalid because it leads you into a wall ";
	out << "or outside of the map ";
	out << "or step on other chracters";
	return out.str();
}


string MoveAction::toString() {
	return "Move your character by one step";
}

MoveAction* MoveAction::clone() {
	return new MoveAction(mainCharacter, characterList, map, moveVec);
}

bool MoveAction::action() {
	bool check = false;
	if (isAllowed()) {
		mainCharacter->moveBy(moveVec);
		mainCharacter->updateCurrentArea(map);
		check = true;
	}
	return check;
}

MoveAction* MoveAction::createMoveAction(GameHelper* helper, helper::Direction d) {
	helper::Vector moveVec = helper::direction[(int)d];
	return new MoveAction(
		helper->getMainCharacter(),
		helper->getCharacterList(),
		helper->getMap(),
		moveVec
	);
}

MoveAction::~MoveAction() {}
