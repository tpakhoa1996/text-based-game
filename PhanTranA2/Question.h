#pragma once

class Role;

class Question {
public:
	using CharacterMap = map<string, string>;
	Question(Role*, string, string);
	string toString();
	string getAnswer();
	Role* getRole();
	void resolve(CharacterMap*);
	~Question();
private:
	string question;
	string answer;
	Role* role;
};

