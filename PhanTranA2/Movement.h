#pragma once
#include "Character.h"
#include "ControlUnit.h"
#include "Game.h"
class Movement : public ControlUnit {
public:
	Movement(GameHelper*);

	bool execute();

	~Movement();
private:
	GameHelper* helper;
};

