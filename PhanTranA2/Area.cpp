#include "stdafx.h"


Area::Area(JSON* config) {
	name = *config->at("name")->getString();
	vertices = new VerticesVec();
	const JSON::Array* verticesConfig = config->at("shape")->getArray();
	for (int i = 0; i < (int)verticesConfig->size(); i += 2) {
		vertices->push_back(new helper::Point {
			*verticesConfig->at(i)->getInt(),
			*verticesConfig->at(i + 1)->getInt()
		});
	}
	if (config->has("items")) {
		const JSON::Array* itemsConfig = config->at("items")->getArray();
		for (const auto& itemConfig : *itemsConfig) {
			items.insert(new Item(itemConfig, this));
		}
	}
	connectedAreas = new AreaVec();
}

const Area::VerticesVec* Area::getVertices() const {
	return vertices;
}

string Area::getName() const {
	return name;
}

bool Area::addItem(Item *item) {
	items.insert(item);
	return true;
}

bool Area::removeItem(Item *item) {
	bool check = false;
	if (hasItem(item)) {
		items.erase(item);
		check = true;
	}
	return check;
}

bool Area::hasItem(Item *item) {
	return items.count(item);
}

Area::ItemVec Area::getItems() {
	return { items.begin(), items.end() };
}

void Area::connect(Area* connectedArea) {
	connectedAreas->push_back(connectedArea);
}

const Area::AreaVec* Area::getConnectedArea() {
	return connectedAreas;
}

Area::~Area() {
	if (vertices != nullptr) {
		delete vertices;
	}
}