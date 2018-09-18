#pragma once
#include "Action.h"
#include "GameHelper.h"

class BackAction :
	public Action {
public:
	BackAction(GameHelper*);
	~BackAction();
	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
private:
	GameHelper *helper = nullptr;
};