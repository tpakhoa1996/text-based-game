#include "stdafx.h"
#include "Question.h"


Question::Question(Role* role, string question, string answer)
	: role(role), question(question), answer(answer)
{}

string Question::toString() {
	return question;
}

string Question::getAnswer() {
	return answer;
}

Role * Question::getRole() {
	return role;
}

void Question::resolve(CharacterMap *characterMap) {
	for (auto entry : *characterMap) {
		question = regex_replace(question, regex("\\{" + entry.first + "\\}"), entry.second);
		answer = regex_replace(answer, regex("\\{" + entry.first + "\\}"), entry.second);
	}
}


Question::~Question() {}
