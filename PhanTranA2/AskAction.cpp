#include "stdafx.h"
#include "AskAction.h"


AskAction::AskAction(GameHelper *helper)
	: helper(helper), Action(new Time(0))
{}

AskAction::~AskAction() {}

bool AskAction::action() {
	bool check = false;
	if (isAllowed()) {
		helper->pushOneControlUnit(
			new AskSuspectCommandGroup(helper)
		);
		check = true;
	}
	return check;
}

string AskAction::toString() {
	return "Ask nearby suspects";
}

Action * AskAction::clone() {
	return new AskAction(helper);
}
