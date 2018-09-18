#pragma once
#include "CommandGroup.h"
#include "GameHelper.h"
class MainCommandGroup :
	public CommandGroup {
public:
	MainCommandGroup(GameHelper*);
	~MainCommandGroup();
};

