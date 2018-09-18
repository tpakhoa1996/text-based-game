#include "stdafx.h"
#include "QuitAction.h"


QuitAction::QuitAction(GameHelper *helper): helper(helper), Action(new Time(0)) {}

bool QuitAction::action() {
	while (helper->goBackOneControlUnit());
	return true;
}

bool QuitAction::isAllowed() {
	return true;
}

string QuitAction::getWarning() {
	return "";
}

string QuitAction::toString() {
	return "Quit game";
}

QuitAction * QuitAction::clone() {
	return new QuitAction(helper);
}


QuitAction::~QuitAction() {}
