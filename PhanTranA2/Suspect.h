#pragma once
#include "Character.h"
#include "Role.h"
#include "JSON.h"

class Suspect : public Character {
public:
	Suspect(string);
	Suspect(JSON*);
	~Suspect();
	void setRole(Role*);
	Role* getRole();
	char getMarker();
	Role::Dialog* getDialog();
	bool isMurderer();
private:
	Role* role = nullptr;
};

