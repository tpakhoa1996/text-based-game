#include "stdafx.h"
#include "Command.h"


Command::Command(string label, Action* action) 
	: label(label), action(action)
{}

Command::Command(string label, Action* action, string commandName) 
	: label(label), action(action), commandName(commandName)
{}

string Command::getLabel() {
	return label;
}

Action* Command::getAction() {
	return action;
}

string Command::getCommandName() {
	string name;
	if (commandName.length()) {
		name = commandName;
	} else {
		name = action->toString();
	}
	return name;
}

Command* Command::clone() {
	return new Command(label, action->clone(), commandName);
}

bool Command::execute() {
	return action->execute();
}

Command::~Command() {
	if (action != nullptr) {
		delete action;
	}
}
