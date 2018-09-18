#pragma once
#include "JSON.h"
#include "Area.h"

class Map;

class Character {
public:
	enum class Class {
		Investigator,
		Suspect
	};

	Character(JSON*);

	Character(string, Class);

	helper::Point getPosition();
	helper::Point getNextPosition(helper::Vector);
	string getName();
	Class getCharacterClass();
	void updateCurrentArea(Map*);
	Area* getCurrentArea();
	virtual char getMarker() = 0;
	void moveTo(helper::Point);
	void moveBy(helper::Vector);

	virtual ~Character() = 0;
protected:
	virtual void setName(string);
private:
	helper::Point position;
	string name;
	Class characterClass;
	Area* currentArea;
};