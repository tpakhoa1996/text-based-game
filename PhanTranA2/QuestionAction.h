#pragma once
#include "Action.h"
#include "Question.h"


class QuestionAction :
	public Action {
public:
	QuestionAction(Question*);
	~QuestionAction();

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
private:
	Question* question;
};

