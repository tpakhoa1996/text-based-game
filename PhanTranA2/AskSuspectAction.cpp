#include "stdafx.h"
#include "AskSuspectAction.h"


AskSuspectAction::AskSuspectAction(GameHelper *helper, Suspect *suspect) 
	: helper(helper), suspect(suspect), Action(new Time(0))
{}

AskSuspectAction::~AskSuspectAction() {}

bool AskSuspectAction::action() {
	bool check = false;
	if (isAllowed()) {
		helper->pushOneControlUnit(
			new QuestionCommandGroup(helper, suspect->getRole())
		);
		check = true;
	}
	return check;
}

string AskSuspectAction::toString() {
	return "Ask " + suspect->getName();
}

Action * AskSuspectAction::clone() {
	return new AskSuspectAction(helper, suspect);
}
