#pragma once
class ControlUnit {
public:
	ControlUnit();
	virtual bool execute() = 0;
	virtual ~ControlUnit() = 0;
};

