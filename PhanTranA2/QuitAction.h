#pragma once
#include "Action.h"
#include "GameHelper.h"

class QuitAction :
	public Action {
public:
	QuitAction(GameHelper*);
	bool action();
	bool isAllowed();
	string getWarning();
	string toString();
	QuitAction* clone();
	~QuitAction();
private:
	GameHelper *helper;
};

