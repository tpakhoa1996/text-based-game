#pragma once
#include "CommandGroup.h"
class QuestionCommandGroup :
	public CommandGroup {
public:
	QuestionCommandGroup(GameHelper*, Role*);
	~QuestionCommandGroup();
};

