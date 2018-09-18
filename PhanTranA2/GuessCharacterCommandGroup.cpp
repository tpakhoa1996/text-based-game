#include "stdafx.h"
#include "GuessCharacterCommandGroup.h"


GuessCharacterCommandGroup::GuessCharacterCommandGroup(GameHelper *helper)
	: CommandGroup(helper)
{
	int index = 0;
	for (auto character : *helper->getCharacterList()) {
		if (character->getCharacterClass() == Character::Class::Suspect) {
			commandList.push_back(new Command(
				to_string(index),
				new GuessCharacterAction(helper, (Suspect*)character)
			));
		}
		index++;
	}
}

GuessCharacterCommandGroup::~GuessCharacterCommandGroup() {}
