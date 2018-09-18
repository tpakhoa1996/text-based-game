#pragma once
#include "Question.h"
#include "JSON.h"

class Suspect;

class Role {
public:
	using Dialog = vector<Question*>;
	using CharacterMap = map<string, string>;
	enum class Type {
		Innocent,
		Murderer
	};
	Role(JSON*);
	Type getType();
	Dialog* getDialog();
	string getName();
	Suspect* getSuspect();
	void setSuspect(Suspect*);
	void resolveDialog(CharacterMap*);
	~Role();
private: 
	Type type;
	Dialog* dialog = nullptr;
	string name;
	Suspect* suspect = nullptr;
};

