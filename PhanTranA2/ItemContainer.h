#pragma once
#include "common.h"
#include "Item.h"

class ItemContainer {
public:
	using ItemVec = vector<Item*>;
	ItemContainer();
	virtual ItemVec getItems() = 0;
	virtual bool addItem(Item*) = 0;
	virtual bool removeItem(Item*) = 0;
	virtual bool hasItem(Item*) = 0;
	virtual ~ItemContainer() = 0;
};