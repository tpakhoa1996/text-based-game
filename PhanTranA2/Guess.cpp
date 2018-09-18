#include "stdafx.h"
#include "Guess.h"


Guess::Guess() {}


Guess::~Guess() {}

void Guess::setItem(Item *item) {
	this->item = item;
}

void Guess::setSuspect(Suspect *suspect) {
	this->suspect = suspect;
}

Item* Guess::getItem() {
	return item;
}

Suspect* Guess::getSuspect() {
	return suspect;
}