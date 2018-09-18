#pragma once
#include "Action.h"
#include "GameHelper.h"

class InventoryAction :
	public Action {
public:
	InventoryAction(GameHelper* helper);
	~InventoryAction();

private:
	GameHelper *helper;

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
};

