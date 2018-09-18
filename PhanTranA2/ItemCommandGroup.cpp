#include "stdafx.h"
#include "ItemCommandGroup.h"


ItemCommandGroup::ItemCommandGroup(GameHelper *helper, ItemContainer *itemContainer)
	: CommandGroup(helper)
{
	context = new ItemGroupContext();
	ItemContainer::ItemVec itemList = itemContainer->getItems();
	for (int i = 0; i < (int)itemList.size(); i++) {
		context->isExamined[itemList[i]] = false;
		commandList.push_back(new Command(
			to_string(i),
			new ItemAction(helper->getMainCharacter(), itemList[i], context)
		));
	}
	commandList.push_back(new Command("b", new BackAction(helper)));
}

ItemCommandGroup::~ItemCommandGroup() {
	if (context != nullptr) {
		delete context;
	}
}
