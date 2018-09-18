#pragma once
#include "Action.h"
class Command {
public:
	Command(string, Action*);
	Command(string, Action*, string);
	string getLabel();
	Action* getAction();
	string getCommandName();
	Command* clone();
	bool execute();
	~Command();
private:
	string label;
	Action* action;
	string commandName;
};

