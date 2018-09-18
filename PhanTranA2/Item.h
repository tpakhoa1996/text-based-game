#pragma once
#include "JSON.h"

class Area;

class Item {
public:
	Item(JSON*, Area*);

	string getName();
	string getDescription();
	int getItemId() const;
	Area* getOriginalArea();
	
	bool isPickable();
	bool isWeapon();

	~Item();

private:
	static int itemCnt;
	string name;
	string description;
	int itemId;
	bool pickable, weapon;
	Area *originalArea;
};

