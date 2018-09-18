#pragma once
class SectionInput {
public:
	SectionInput(istream&);
	string name;
	stringstream stream;
	~SectionInput();
};

