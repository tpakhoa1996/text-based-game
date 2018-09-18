#pragma once
#include "CommandGroup.h"
class AskSuspectCommandGroup :
	public CommandGroup {
public:
	AskSuspectCommandGroup(GameHelper *helper);
	~AskSuspectCommandGroup();
};

