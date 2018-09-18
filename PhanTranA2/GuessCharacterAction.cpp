#include "stdafx.h"
#include "GuessCharacterAction.h"


GuessCharacterAction::GuessCharacterAction(GameHelper *helper, Suspect *suspect)
	: helper(helper), suspect(suspect), Action(new Time(0))
{}

GuessCharacterAction::~GuessCharacterAction() {}

bool GuessCharacterAction::action() {
	bool check = true;
	if (isAllowed()) {
		helper->getGuess()->setSuspect(suspect);
		helper->pushOneControlUnit(
			new GuessItemCommandGroup(helper)
		);
		check = true;
	}
	return check;
}

string GuessCharacterAction::toString() {
	return "Guess suspect " + suspect->getName();
}

Action * GuessCharacterAction::clone() {
	return new GuessCharacterAction(helper, suspect);
}
