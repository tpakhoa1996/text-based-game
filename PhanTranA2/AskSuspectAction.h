#pragma once
#include "Action.h"
#include "Suspect.h"

class AskSuspectAction :
	public Action {
public:
	AskSuspectAction(GameHelper*, Suspect*);
	~AskSuspectAction();

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
private:
	GameHelper *helper;
	Suspect *suspect;
};

