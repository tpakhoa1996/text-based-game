#pragma once
#include "Item.h"

class ItemGroupContext {
	friend class ItemAction;
	friend class ItemCommandGroup;
public:
	ItemGroupContext();
	~ItemGroupContext();
private:
	map<Item*, bool> isExamined;
};

