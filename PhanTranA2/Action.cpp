#include "stdafx.h"
#include "Action.h"


Action::Action(Time* timeTaken): timeTaken(timeTaken) {}

bool Action::checkTimeLimit() {
	return timeTaken->checkLimit();
}

bool Action::isAllowed() {
	return checkTimeLimit();
}

string Action::getWarning() {
	string warning;
	if (!isAllowed()) {
		warning = "You dont have enough time to execute this action";
	}
	return warning;
}

bool Action::execute() {
	bool success = false;
	if (isAllowed() && action()) {
		timeTaken->consume();
		success = true;
	}
	return success;
}

int Action::getTime() {
	return timeTaken->getTime();
}

Action::~Action() {
	if (timeTaken != nullptr) {
		delete timeTaken;
	}
}
