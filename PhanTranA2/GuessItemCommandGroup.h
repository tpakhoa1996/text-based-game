#pragma once
#include "CommandGroup.h"
class GuessItemCommandGroup :
	public CommandGroup {
public:
	GuessItemCommandGroup(GameHelper*);
	~GuessItemCommandGroup();
};

