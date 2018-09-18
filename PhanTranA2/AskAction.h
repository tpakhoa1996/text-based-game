#pragma once
#include "Action.h"
class AskAction :
	public Action {
public:
	AskAction(GameHelper*);
	~AskAction();
private:
	GameHelper *helper;

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
};

