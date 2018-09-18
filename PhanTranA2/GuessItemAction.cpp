#include "stdafx.h"
#include "GuessItemAction.h"


GuessItemAction::GuessItemAction(GameHelper *helper, Item *item)
	: Action(new Time(0)), helper(helper), item(item)
{}

GuessItemAction::~GuessItemAction() {}

bool GuessItemAction::action() {
	bool check = false;
	if (isAllowed()) {
		Guess* guess = helper->getGuess();
		guess->setItem(item);
		
		if (guess->getSuspect()->isMurderer() && guess->getItem()->isWeapon()) {
			cout << "Your guess is correct! Congratulation!" << endl;
		} else {
			cout << "Unfortunately, your guess is almost correct. Bad luck." << endl;
		}
		system("pause");

		while (helper->goBackOneControlUnit());

		check = true;
	}
	return check;
}

string GuessItemAction::toString() {
	return "Guess item " + item->getName() + " from " + item->getOriginalArea()->getName();
}

Action * GuessItemAction::clone() {
	return new GuessItemAction(helper, item);
}
