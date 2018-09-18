#include "stdafx.h"
#include "Suspect.h"

Suspect::Suspect(string name) :
	Character(name, Character::Class::Suspect) {}

Suspect::Suspect(JSON* config) :
	Character(config) {}

Role::Dialog* Suspect::getDialog() {
	return role->getDialog();
}

char Suspect::getMarker() {
	return tolower(getName()[0]);
}

bool Suspect::isMurderer() {
	return role->getType() == Role::Type::Murderer;
}

Suspect::~Suspect() {}

void Suspect::setRole(Role *newRole) {
	role = newRole;
}

Role * Suspect::getRole() {
	return role;
}
