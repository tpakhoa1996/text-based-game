#include "stdafx.h"
#include "DiscoverAction.h"


DiscoverAction::DiscoverAction(GameHelper* helper) 
	: helper(helper), Action(new Time(1))
{}

DiscoverAction::~DiscoverAction() {}

bool DiscoverAction::action() {
	bool check = false;
	if (isAllowed()) {
		helper->pushOneControlUnit(
			new ItemCommandGroup(helper, helper->getMainCharacter()->getCurrentArea())
		);
		check = true;
	}
	return check;
}

string DiscoverAction::toString() {
	return "Discover " + helper->getMainCharacter()->getCurrentArea()->getName();
}

Action * DiscoverAction::clone() {
	return new DiscoverAction(helper);
}