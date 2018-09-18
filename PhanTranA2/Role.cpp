#include "stdafx.h"
#include "Role.h"


Role::Role(JSON* config) {
	name = *config->at("name")->getString();
	dialog = new Dialog();
	const JSON::Array *dialogConfig = config->at("dialog")->getArray();
	for (int i = 0; i < (int)dialogConfig->size(); i++) {
		const JSON::Array *question = dialogConfig->at(i)->getArray();
		dialog->push_back(new Question(
			this,
			*question->at(0)->getString(),
			*question->at(1)->getString()
		));
	}

	bool isCriminal = false;
	if (config->has("criminal")) {
		isCriminal = *config->at("criminal")->getBool();
	}

	if (isCriminal) {
		type = Type::Murderer;
	} else {
		type = Type::Innocent;
	}
}

Role::Dialog* Role::getDialog() {
	return dialog;
}

string Role::getName() {
	return name;
}

Suspect * Role::getSuspect() {
	return suspect;
}

void Role::setSuspect(Suspect *suspect) {
	this->suspect = suspect;
}

void Role::resolveDialog(CharacterMap *characterMap) {
	for (auto question : *dialog) {
		question->resolve(characterMap);
	}
}

Role::Type Role::getType() {
	return type;
}


Role::~Role() {
	if (dialog != nullptr) {
		for (auto question : *dialog) {
			delete question;
		}
		delete dialog;
	}
}
