#pragma once
#include "CommandGroup.h"
#include "Character.h"
#include "GameHelper.h"
#include "ItemContainer.h"
#include "ItemGroupContext.h"

class ItemCommandGroup : public CommandGroup {
public:
	ItemCommandGroup(GameHelper*, ItemContainer*);
	~ItemCommandGroup();
private:
	ItemGroupContext *context = nullptr;
};

