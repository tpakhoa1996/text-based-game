#include "stdafx.h"
#include "InstructionAction.h"


InstructionAction::InstructionAction(GameHelper *helper): Action(new Time(0)), helper(helper) {}

InstructionAction::~InstructionAction() {}

bool InstructionAction::action() {
	cout << helper->getInstruction() << endl;
	system("pause");
	return true;
}

string InstructionAction::toString() {
	return "Show instruction";
}

Action * InstructionAction::clone() {
	return new InstructionAction(helper);
}
