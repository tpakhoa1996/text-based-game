#include "stdafx.h"
#include "QuestionAction.h"


QuestionAction::QuestionAction(Question *question)
	: question(question), Action(new Time(1))
{}

QuestionAction::~QuestionAction() {}

bool QuestionAction::action() {
	bool check = false;
	if (isAllowed()) {
		cout << question->getRole()->getSuspect()->getName();
		cout << " anser: " << question->getAnswer() << endl;
		system("pause");
		check = true;
	}
	return check;
}

string QuestionAction::toString() {
	return question->toString();
}

Action * QuestionAction::clone() {
	return new QuestionAction(question);
}
