#pragma once
#include "Action.h"
#include "GameHelper.h"

class DiscoverAction :
	public Action {
public:
	DiscoverAction(GameHelper*);
	~DiscoverAction();
private:
	GameHelper *helper = nullptr;

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
};

