#pragma once
#include "Action.h"
#include "GameHelper.h"
class InstructionAction :
	public Action {
public:
	InstructionAction(GameHelper*);
	~InstructionAction();

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
private:
	GameHelper* helper;
};