#include "stdafx.h"
#include "MainCommandGroup.h"


MainCommandGroup::MainCommandGroup(GameHelper* helper): CommandGroup(helper) {
	commandList.push_back(new Command(
		"help",
		new InstructionAction(helper)
	));
	commandList.push_back(new Command(
		"map",
		new MapAction(helper)
	));
	commandList.push_back(new Command(
		"discover",
		new DiscoverAction(helper)
	));
	commandList.push_back(new Command(
		"ask",
		new AskAction(helper)
	));
	commandList.push_back(new Command(
		"item",
		new InventoryAction(helper)
	));
	commandList.push_back(new Command(
		"move",
		new MovementAction(helper),
		"Move your character around"
	));
	commandList.push_back(new Command(
		"solve",
		new GuessAction(helper)
	));
	commandList.push_back(new Command(
		"q",
		new QuitAction(helper)
	));
}


MainCommandGroup::~MainCommandGroup() {}
