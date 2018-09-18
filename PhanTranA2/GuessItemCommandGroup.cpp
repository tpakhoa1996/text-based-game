#include "stdafx.h"
#include "GuessItemCommandGroup.h"


GuessItemCommandGroup::GuessItemCommandGroup(GameHelper *helper)
	: CommandGroup(helper)
{
	int index = 0;
	for (auto item : helper->getMainCharacter()->getItems()) {
		commandList.push_back(new Command(
			to_string(index),
			new GuessItemAction(helper, item)
		));
		index++;
	}
}

GuessItemCommandGroup::~GuessItemCommandGroup() {}
