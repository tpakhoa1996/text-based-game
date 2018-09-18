#include "stdafx.h"
#include "CommandGroup.h"

CommandGroup::CommandGroup(GameHelper *helper): helper(helper) {}

bool CommandGroup::execute() {
	string commandTitle = "Command";
	string timeTitle = "Time";
	string actionTitle = "Action";

	int commandLen = commandTitle.length();
	int timeLen = timeTitle.length();
	int actionStrLen = actionTitle.length();
	for (auto command: commandList) {
		Action* action = command->getAction();
		commandLen = max(commandLen, (int)command->getLabel().length());
		timeLen = max(timeLen, (int)to_string(action->getTime()).length());
		actionStrLen = max(actionStrLen, (int)command->getCommandName().length());
	}
	cout << endl << endl;
	cout << " " << setw(commandLen) << left << commandTitle << " | ";
	cout << setw(timeLen) << left << timeTitle << " | ";
	cout << actionTitle << endl;
	cout << setw(commandLen + timeLen + actionStrLen + 7) << setfill('-') << "" << endl;
	cout << setw(0) << setfill(' ');
	for (auto command : commandList) {
		Action* action = command->getAction();
		cout << " " << setw(commandLen) << left << command->getLabel() << " | ";
		cout << setw(timeLen) << right << action->getTime() << " | ";
		cout << command->getCommandName() << endl;
	}
	cout << setw(commandLen + timeLen + actionStrLen + 7) << setfill('-') << "" << endl;

	string currentAreaName = helper->getMainCharacter()->getCurrentArea()->getName();
	string areaStr = "You are currently in ";
	int areaLen = areaStr.length() + currentAreaName.length();
	string timerStr = "Your remaining time is: ";
	int timerLen = timerStr.length() + to_string(Time::getRemainingTime()).length();
	int infoLen = max(areaLen, timerLen);

	cout << endl;
	cout << "+" << setw(infoLen + 2) << setfill('-') << "" << "+" << endl;
	cout << "| " << setw(infoLen) << setfill(' ') << left << (areaStr + currentAreaName) << " |" << endl;
	cout << "| " << setw(infoLen) << setfill(' ') << left << (timerStr + to_string(Time::getRemainingTime())) << " |" << endl;
	cout << "+" << setw(infoLen + 2) << setfill('-') << "" << "+" << endl;
	cout << setw(0) << setfill(' ');

	string commandLabel;
	int commandIndex = 0;
	enum InputState {
		Begin, InvalidCommand, UnexecutableCommand
	};
	int inputFlag = InputState::Begin;
	do {
		switch (inputFlag) {
		case InputState::Begin:
			cout << "Enter a command: ";
			break;
		case InputState::InvalidCommand:
			cout << "Invalide command!" << endl;
			cout << "Please enter a command again: ";
			break;
		case InputState::UnexecutableCommand:
			cout << commandList[commandIndex]->getAction()->getWarning() << endl;
			cout << "Please enter a command again: ";
			break;
		}
		getline(cin, commandLabel);
		commandIndex = getCommandByLabel(commandLabel);
		if (commandIndex < 0) {
			inputFlag = InputState::InvalidCommand;
		} else if (!commandList[commandIndex]->getAction()->isAllowed()) {
			inputFlag = InputState::UnexecutableCommand;
		}
	} while (commandIndex < 0);
	cout << endl;
	
	Command* command = commandList[commandIndex]->clone();
	bool result = command->execute();
	delete command;
	return result;
}

int CommandGroup::getCommandByLabel(string label) {
	int result = -1;
	for (int i = 0; i < (int)commandList.size(); i ++) {
		if (commandList[i]->getLabel() == label) {
			result = i;
			break;
		}
	}
	return result;
}

CommandGroup::~CommandGroup() {
	for (auto command : commandList) {
		delete command;
	}
};