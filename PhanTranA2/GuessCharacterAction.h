#pragma once
#include "Action.h"
class GuessCharacterAction :
	public Action {
public:
	GuessCharacterAction(GameHelper*, Suspect*);
	~GuessCharacterAction();

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;
private:
	GameHelper *helper;
	Suspect *suspect;

};

