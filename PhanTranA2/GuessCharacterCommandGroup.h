#pragma once
#include "CommandGroup.h"
class GuessCharacterCommandGroup :
	public CommandGroup {
public:
	GuessCharacterCommandGroup(GameHelper*);
	~GuessCharacterCommandGroup();
};

