#pragma once
#include "Action.h"
#include "GameHelper.h"
class MovementAction :
	public Action {
public:
	MovementAction(GameHelper*);
	~MovementAction();
private:
	GameHelper *helper;

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
};

