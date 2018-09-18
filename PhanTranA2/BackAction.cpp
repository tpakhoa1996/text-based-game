#include "stdafx.h"
#include "BackAction.h"


BackAction::BackAction(GameHelper *helper) : Action(new Time(0)), helper(helper) {}

BackAction::~BackAction() {}

bool BackAction::action() {
	return helper->goBackOneControlUnit();
}

string BackAction::toString() {
	return "Go back";
}

Action * BackAction::clone() {
	return new BackAction(helper);
}
