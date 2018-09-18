#pragma once
#include "Action.h"
#include "GameHelper.h"

class GuessAction :
	public Action {
public:
	GuessAction(GameHelper*);
	~GuessAction();

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
private:
	GameHelper *helper = nullptr;
};

