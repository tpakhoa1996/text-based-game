#include "stdafx.h"
#include "MapAction.h"


MapAction::MapAction(GameHelper *helper)
	: helper(helper), Action(new Time(0))
{}

MapAction::~MapAction() {}

bool MapAction::action() {
	string overalMap = helper->getMap()->renderOveralMap(
		helper->getMainCharacter()
	);
	cout << overalMap << endl;
	system("pause");
	return true;
}

string MapAction::toString() {
	return "Show overal map";
}

Action * MapAction::clone() {
	return new MapAction(helper);
}
