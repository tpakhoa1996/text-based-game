#include "stdafx.h"
#include "GuessAction.h"


GuessAction::GuessAction(GameHelper *helper)
	: helper(helper), Action(new Time(0))
{}

GuessAction::~GuessAction() {}

bool GuessAction::action() {
	bool check = false;
	if (isAllowed()) {
		helper->pushOneControlUnit(
			new GuessCharacterCommandGroup(helper)
		);
		check = true;
	}
	return check;
}

string GuessAction::toString() {
	return "Solve the crime";
}

Action * GuessAction::clone() {
	return new GuessAction(helper);
}
