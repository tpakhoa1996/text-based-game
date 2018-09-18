#include "stdafx.h"
#include "Character.h"


Character::Character(string name, Class characterClass) :
	name(name), characterClass(characterClass) {}

Character::Character(JSON* config) {
	name = *config->at("name")->getString();

	string className = *config->at("class")->getString();
	if (className == "suspect") {
		characterClass = Class::Suspect;
	} else if (className == "investigator") {
		characterClass = Class::Investigator;
	}

	position = {
		*config->at("position")->at(0)->getInt(),
		*config->at("position")->at(1)->getInt()
	};
};


void Character::moveTo(helper::Point p) {
	position.first = p.first;
	position.second = p.second;
}

void Character::moveBy(helper::Vector d) {
	moveTo(getNextPosition(d));
}

helper::Point Character::getPosition() {
	return position;
}

helper::Point Character::getNextPosition(helper::Vector d) {
	return {
		position.first + d.first,
		position.second + d.second
	};
}

Character::Class Character::getCharacterClass() {
	return characterClass;
}

void Character::setName(string newName) {
	name = newName;
}

string Character::getName() {
	return name;
}

void Character::updateCurrentArea(Map* map) {
	Area* temp = map->getAreaFromPoint(position);
	if (temp != nullptr) {
		currentArea = temp;
	}
}

Area* Character::getCurrentArea() {
	return currentArea;
}

Character::~Character() {}
