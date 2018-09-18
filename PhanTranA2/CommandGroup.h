#pragma once
#include "common.h"
#include "Command.h"
#include "ControlUnit.h"

class GameHelper;

class CommandGroup : public ControlUnit {
public:
	using CommandVec = vector<Command*>;
	CommandGroup(GameHelper*);
	bool execute();
	virtual ~CommandGroup() = 0;
protected:
	CommandVec commandList;
	GameHelper *helper;

	int getCommandByLabel(string);
};

