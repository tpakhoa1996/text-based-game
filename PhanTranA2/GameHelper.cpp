#include "stdafx.h"
#include "GameHelper.h"


GameHelper::GameHelper() {}

void GameHelper::pushOneControlUnit(ControlUnit *controlUnit) {
	controlStack->push(controlUnit);
}

bool GameHelper::goBackOneControlUnit() {
	bool check = false;
	if (!controlStack->empty()) {
		delete controlStack->top();
		controlStack->pop();
		check = true;
	}
	return check;
}

Map* GameHelper::getMap() {
	return map;
}

GameHelper::CharacterVec* GameHelper::getCharacterList() {
	return characterList;
}

Investigator* GameHelper::getMainCharacter() {
	return mainCharacter;
}

string GameHelper::getInstruction() {
	return instruction;
}

Guess * GameHelper::getGuess() {
	return guess;
}

GameHelper::~GameHelper() {
	if (map != nullptr) delete map;
	if (guess != nullptr) delete guess;
	if (characterList != nullptr) {
		for (auto character : *characterList) {
			delete character;
		}
	}
	if (controlStack != nullptr) {
		while (!controlStack->empty()) {
			delete controlStack->top();
			controlStack->pop();
		}
	}
	for (auto role : roles) {
		delete role;
	}
}