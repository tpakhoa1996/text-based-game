#include "stdafx.h"
#include "SectionInput.h"


SectionInput::SectionInput(istream& input) {
	while (name.empty() && !input.eof()) {
		getline(input, name);
		name = helper::trim(name);
	}
	if (!name.empty()) {
		while (1) {
			string line;
			getline(input, line);
			string endSection = helper::trim(line);
			if (endSection == "End_Section") {
				break;
			}
			stream << line << endl;
		}
	}
}


SectionInput::~SectionInput() {}
