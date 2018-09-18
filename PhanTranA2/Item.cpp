#include "stdafx.h"
#include "Item.h"


int Item::itemCnt = 0;

Item::Item(JSON* config, Area *originalArea): itemId(itemCnt++) {
	this->originalArea = originalArea;
	name = *config->at("name")->getString();
	description = *config->at("description")->getString();
	pickable = false;
	weapon = false;
	if (config->has("pickable")) {
		pickable = *config->at("pickable")->getBool();
	}
	if (config->has("weapon")) {
		weapon = *config->at("weapon")->getBool();
	}
}

string Item::getName() {
	return name;
}

string Item::getDescription() {
	return description;
}

int Item::getItemId() const {
	return itemId;
}

Area * Item::getOriginalArea() {
	return originalArea;
}

bool Item::isPickable() {
	return pickable;
}

bool Item::isWeapon() {
	return weapon;
}

Item::~Item() {}