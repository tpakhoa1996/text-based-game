#include "stdafx.h"
#include "InventoryAction.h"


InventoryAction::InventoryAction(GameHelper * helper)
	: Action(new Time(1)), helper(helper)
{}

InventoryAction::~InventoryAction() {}

bool InventoryAction::action() {
	bool check = false;
	if (isAllowed()) {
		helper->pushOneControlUnit(
			new ItemCommandGroup(helper, helper->getMainCharacter())
		);
		check = true;
	}
	return check;
}

string InventoryAction::toString() {
	return "Your inventory";
}

Action * InventoryAction::clone() {
	return new InventoryAction(helper);
}
