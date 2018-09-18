#pragma once
#include "Action.h"
#include "GameHelper.h"
class MapAction :
	public Action {
public:
	MapAction(GameHelper*);
	~MapAction();

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
private:
	GameHelper *helper;
};

