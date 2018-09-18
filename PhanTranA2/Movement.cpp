#include "stdafx.h"
#include "Movement.h"


Movement::Movement(GameHelper* helper) : helper(helper) {}

bool Movement::execute() {
	string playMap = helper->getMap()->renderPlayMap(
		helper->getCharacterList(),
		helper->getMainCharacter()->getCurrentArea()
	);
	cout << playMap << endl;

	enum InputState {
		Begin, Invalid
	};
	InputState inputFlag = Begin;
	string command;
	set<string> s{ "q", "a", "w", "d", "s" };
	while (1) {
		switch (inputFlag) {
		case Begin:
			cout << "Enter a movement command or 'q' to continue: ";
			break;
		case Invalid:
			cout << "You have entered an invalid command" << endl;
			cout << "Please enter again a movement command or 'q' to continue: ";
			break;
		}
		getline(cin, command);
		if (!s.count(command)) {
			inputFlag = Invalid;
		} else {
			break;
		}
	}

	MoveAction *move = nullptr; 
	switch (command[0]) {
	case 'w':
		move = MoveAction::createMoveAction(helper, helper::Direction::Up);
		break;
	case 'd':
		move = MoveAction::createMoveAction(helper, helper::Direction::Right);
		break;
	case 's':
		move = MoveAction::createMoveAction(helper, helper::Direction::Down);
		break;
	case 'a':
		move = MoveAction::createMoveAction(helper, helper::Direction::Left);
		break;
	case 'q':
		helper->goBackOneControlUnit();
	}

	bool check = true;
	if (move != nullptr) {
		if (!move->action()) {
			cout << move->getWarning() << endl;
			check = false;
		}
	}

	return check;
}

Movement::~Movement() {}
