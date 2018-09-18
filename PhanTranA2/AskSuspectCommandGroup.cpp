#include "stdafx.h"
#include "AskSuspectCommandGroup.h"


AskSuspectCommandGroup::AskSuspectCommandGroup(GameHelper * helper)
	: CommandGroup(helper)
{
	Investigator *mainCharacter = helper->getMainCharacter();
	GameHelper::CharacterVec *characterList = helper->getCharacterList();
	helper::Point mainPosition = mainCharacter->getPosition();
	for (int i = 0; i < (int)characterList->size(); i++) {
		Character *character = characterList->at(i);
		helper::Point position = character->getPosition();
		int x = abs(mainPosition.first - position.first);
		int y = abs(mainPosition.second - position.second);
		if (
			character->getCharacterClass() == Character::Class::Suspect
			&& x + y == 1
		) {
			commandList.push_back(new Command(
				to_string(i),
				new AskSuspectAction(helper, (Suspect*)character)
			));
		}
	}
	commandList.push_back(new Command(
		"b",
		new BackAction(helper)
	));
}

AskSuspectCommandGroup::~AskSuspectCommandGroup() {}
