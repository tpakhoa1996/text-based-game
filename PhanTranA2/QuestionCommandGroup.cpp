#include "stdafx.h"
#include "QuestionCommandGroup.h"


QuestionCommandGroup::QuestionCommandGroup(GameHelper* helper, Role *role)
	: CommandGroup(helper)
{
	Role::Dialog *dialog = role->getDialog();
	for (int i = 0; i < (int)dialog->size(); i ++) {
		commandList.push_back(new Command(
			to_string(i),
			new QuestionAction(dialog->at(i))
		));
	}
	commandList.push_back(new Command(
		"b",
		new BackAction(helper)
	));
}

QuestionCommandGroup::~QuestionCommandGroup() {}