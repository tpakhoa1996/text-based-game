#pragma once
#include "Character.h"
#include "Item.h"
#include "Area.h"
#include "Map.h"
#include "JSON.h"
#include "ItemContainer.h"

class Investigator : public Character, public ItemContainer {
public:
	using ItemSet = set<Item*>;
	Investigator(string);
	Investigator(JSON*);
	~Investigator();
	void setName(string);
	using MovementCmdMap = map<string, helper::Vector>;
	bool addItem(Item*) override;
	bool removeItem(Item*) override;
	ItemVec getItems() override;
	virtual bool hasItem(Item*) override;
	char getMarker();
private:
	ItemSet bag;
};