#pragma once
#include "Time.h"

class Action {
public:
	Action(Time*);
	bool checkTimeLimit();
	bool execute();
	virtual bool action() = 0;
	virtual bool isAllowed();
	virtual string getWarning();
	virtual string toString() = 0;
	virtual Action* clone() = 0;
	int getTime();
	virtual ~Action() = 0;
private:
	Time* timeTaken = nullptr;
};

