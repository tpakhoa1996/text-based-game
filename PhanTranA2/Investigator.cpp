#include "stdafx.h"
#include "Investigator.h"


Investigator::Investigator(string name) 
	: Character(name, Character::Class::Investigator)
{}

Investigator::Investigator(JSON* config) :
	Character(config) {}

void Investigator::setName(string name) {
	Character::setName(name);
}

bool Investigator::addItem(Item* item) {
	bool check = false;
	Area *currentArea = getCurrentArea();
	if (currentArea != nullptr && currentArea->hasItem(item)) {
		if (currentArea->removeItem(item)) {
			bag.insert(item);
			check = true;
		}
	}
	return check;
}

bool Investigator::removeItem(Item* item) {
	bool check = false;
	Area *currentArea = getCurrentArea();
	if (currentArea != nullptr && hasItem(item)) {
		if (currentArea->addItem(item)) {
			bag.erase(item);
			check = true;
		}
	}
	return check;
}

char Investigator::getMarker() {
	return toupper(getName()[0]);
}

Investigator::ItemVec Investigator::getItems() {
	return { bag.begin(), bag.end() };
}

bool Investigator::hasItem(Item *item) {
	return bag.count(item);
}

Investigator::~Investigator() {
	for (auto item : bag) {
		delete item;
	}
}
