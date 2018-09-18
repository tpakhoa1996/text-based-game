#include "stdafx.h"
#include "ItemAction.h"


ItemAction::ItemAction(
	Investigator *mainCharacter, Item *item, ItemGroupContext *context
)
	: 
	mainCharacter(mainCharacter), item(item), Action(new Time(1)), context(context)
{
	updateState();
}

ItemAction::~ItemAction() {}

bool ItemAction::action() {
	bool check = false;
	if (isAllowed()) {
		for (auto &x : context->isExamined) {
			if (x.first != item) {
				x.second = false;
			}
		}
		updateState();
		switch (state) {
		case ActionState::Examine:
			cout << "Description of item '" << item->getName() << "': " << endl;
			cout << "    " << item->getDescription() << endl;
			if (item->isPickable()) {
				cout << "    " << "This item is pickable" << endl;
				context->isExamined[item] = true;
			} else {
				cout << "    " << "This item is NOT pickable" << endl;
				context->isExamined[item] = false;
			}
			system("pause");
			check = true;
			break;
		case ActionState::Drop:
			if (mainCharacter->removeItem(item)) {
				check = true;
			}
			break;
		case ActionState::Pick:
			if (mainCharacter->addItem(item)) {
				check = true;
			}
			break;
		}
	}
	return check;
}

string ItemAction::toString() {
	ostringstream out;
	updateState();
	switch (state) {
	case ActionState::Examine:
		out << "Examine ";
		break;
	case ActionState::Drop:
		out << "Drop ";
		break;
	case ActionState::Pick:
		out << "Pick ";
		break;
	}
	out << item->getName();
	return out.str();
}

Action * ItemAction::clone() {
	return new ItemAction(mainCharacter, item, context);
}

void ItemAction::updateState() {
	if (!context->isExamined[item]) {
		state = ActionState::Examine;
	} else {
		if (mainCharacter->hasItem(item)) {
			state = ActionState::Drop;
		} else {
			state = ActionState::Pick;
		}
	}
}
