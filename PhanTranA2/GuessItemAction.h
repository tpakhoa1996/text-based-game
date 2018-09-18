#pragma once
#include "Action.h"
class GuessItemAction :
	public Action {
public:
	GuessItemAction(GameHelper*, Item*);
	~GuessItemAction();

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
private:
	GameHelper *helper;
	Item* item;
};

