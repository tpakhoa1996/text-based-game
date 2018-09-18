#include "stdafx.h"
#include "MovementAction.h"


MovementAction::MovementAction(GameHelper *helper)
	: Action(new Time(0)), helper(helper)
{}

MovementAction::~MovementAction() {}

bool MovementAction::action() {
	bool check = false;
	if (isAllowed()) {
		helper->pushOneControlUnit(
			new Movement(helper)
		);
		check = true;
	}
	return check;
}

string MovementAction::toString() {
	return "Move your character around";
}

Action * MovementAction::clone() {
	return new MovementAction(helper);
}
