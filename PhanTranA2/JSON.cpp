#include "stdafx.h"
#include "JSON.h"


JSON::JSON() {}

JSON* JSON::read(istream& in) {
	return get<0>(parseObject(in, 1, 0));
}

JSON::Value JSON::parseObject(istream& in, int line, int col) {
	bool inObject = false;
	bool readDelim = false;
	char needDelim = 0;
	bool readValue = false;
	bool readKey = false;
	bool checkRead = false;
	bool allowEnd = false;
	string key;
	JSON* result = new JSON();
	result->valueType = Type::Object;
	result->objectVal = new  Object();
	while (!in.eof()) {
		char c = in.get();
		col++;
		if (c == '\n') {
			line++;
			col = 0;
		}
		if (!inObject) {
			if (c == ' ' || c == '\n') {
				continue;
			} else if (c == '{') {
				inObject = true;
				readKey = true;
				allowEnd = true;
			} else {
				throwError(line, col);
			}
		}

		if (inObject) {
			if (readKey) {
				NextValue val = readNextValue(in, line, col);
				char nextC;
				JSON* jsonValue;
				tie(jsonValue, nextC, line, col) = val;
				if (nextC == '}' && allowEnd) {
					in.get();
					checkRead = true;
					break;
				} else if (nextC == ' ' || nextC == '\n') {
					continue;
				} else if (jsonValue != nullptr && jsonValue->getValueType() == Type::String)  {
					key = *(jsonValue->getString());
					readKey = false;
					readDelim = true;
					needDelim = ':';
					allowEnd = false;
				} else {
					throwError(line, col + 1);
				}
			} else if (readDelim) {
				if (c == ' ' || c == '\n') {
					continue;
				} else if (c == needDelim) {
					readDelim = false;
					if (needDelim == ':') {
						readValue = true;
					} else if (needDelim == ',') {
						readKey = true;
						allowEnd = false;
					}
				} else if (c == '}' && allowEnd) {
					checkRead = true;
					break;
				} else {
					throwError(line, col);
				}
			} else if (readValue) {
				NextValue val = readNextValue(in, line, col);
				JSON* jsonVal;
				char nextC;
				tie(jsonVal, nextC, line, col) = val;
				if (nextC == ' ' || nextC == '\n') {
					continue;
				} else if (jsonVal != nullptr && jsonVal->getValueType() != Type::None) {
					result->objectVal->insert({ key, jsonVal });
					readValue = false;
					readDelim = true;
					needDelim = ',';
					allowEnd = true;
				} else {
					throwError(line, col + 1);
				}
			}
		}
	}

	if (!checkRead) {
		throwError(line, col);
		return { nullptr, line, col };
	} else {
		return { result, line, col };
	}

}



void JSON::throwError(int line, int col) {
	cerr << "JSON parser: Error at line " << line << ", and col " << col;
	exit(EXIT_FAILURE);
}

JSON::Value JSON::parseArray(istream& in, int line, int col) {
	JSON* result = new JSON();
	result->arrayVal = new Array();
	result->valueType = Type::Array;

	bool checkRead = false;
	bool inArray = false;
	bool readVal = false;
	bool readDelim = false;
	bool allowEnd = false;
	while (!in.eof()) {
		char c = in.get();
		col++;
		if (c == '\n') {
			line++;
			col = 0;
		}
		if (!inArray) {
			if (c == '\n' || c == ' ') {
				continue;
			} else if (c == '[') {
				inArray = true;
				readVal = true;
				allowEnd = true;
			} else {
				throwError(line, col);
			}
		}
		if (inArray) {
			if (readVal) {
				NextValue val = readNextValue(in, line, col);
				char nextC;
				JSON* jsonValue;
				tie(jsonValue, nextC, line, col) = val;
				if (nextC == ' ' || nextC == '\n') {
					continue;
				} else if (nextC == ']' && allowEnd) {
					in.get();
					checkRead = true;
					break;
				} else if (jsonValue != nullptr && jsonValue->getValueType() != Type::None) {
					result->arrayVal->push_back(jsonValue);
					readVal = false;
					readDelim = true;
					allowEnd = true;
				} else {
					throwError(line, col + 1);
				}
			} else if (readDelim) {
				if (c == ' ' || c == '\n') {
					continue;
				} else if (c == ',') {
					readDelim = false;
					readVal = true;
					allowEnd = false;
				} else if (c == ']' && allowEnd) {
					checkRead = true;
					break;
				} else {
					throwError(line, col);
				}
			}
		}
	}

	if (checkRead) {
		return { result, line, col };
	} else {
		throwError(line, col);
		return { nullptr, line, col };
	}
}

JSON::NextValue JSON::readNextValue(istream& in, int line, int col) {
	char nextC = in.peek();
	bool check = false;
	Value val;
	JSON *jsonVal = nullptr;
	if (nextC == '"') {
		val = JSON::parseString(in, line, col);
		check = true;
	} else if (nextC == 't' || nextC == 'f') {
		val = JSON::parseBool(in, line, col);
		check = true;
	} else if ((nextC >= '0' && nextC <= '9') || nextC == '-') {
		val = JSON::parseInt(in, line, col);
		check = true;
	} else if (nextC == '[') {
		val = JSON::parseArray(in, line, col);
		check = true;
	} else if (nextC == '{') {
		val = JSON::parseObject(in, line, col);
		check = true;
	}
	if (check) {
		tie(jsonVal, line, col) = val;
	}
	return { jsonVal, nextC, line, col };
}

JSON::Value JSON::parseInt(istream& in, int line, int col) {
	int val = 0;
	bool inNumber = false;
	int sign = 1;
	int checkRead = false;
	while (!in.eof()) {
		char c = in.get();
		col++;

		if (!inNumber) {
			if (c == ' ' || c == '\n') {
				continue;
			} else if ((c >= '0' && c <= '9') || (c == '-')) {
				inNumber = true;
			} else {
				throwError(line, col);
			}
		}

		if (inNumber) {
			if (c == '-') {
				sign = -1;
			} else {
				val = val * 10 + (c - '0');
				checkRead = true;
			}
			char nextC = in.peek();
			if (nextC == char_traits<char>::eof() || nextC < '0' || nextC > '9') {
				break;
			}
		}
	}
	if (!checkRead) {
		throwError(line, col);
		return { nullptr, line, col };
	} else {
		JSON* result = new JSON();
		result->valueType = Type::Int;
		result->intVal = new int { sign * val };
		return { result, line, col };
	}
}

JSON::Value JSON::parseString(istream& in, int line, int col) {
	string s;
	bool inString = false;
	bool readCheck = false;
	while (!in.eof()) {
		char c = in.get();
		col++;
		if (c == '\n') {
			line++;
			col = 0;
		}
		if (!inString) {
			if (c == '\n' || c == ' ') {
				continue;
			} else if (c == '"') {
				inString = true;
			} else {
				throwError(line, col);
			}
		} else if (inString) {
			if (c == '"') {
				readCheck = true;
				break;
			} else {
				s.push_back(c);
			}
		}
	}
	if (readCheck) {
		JSON*  result = new JSON();
		result->stringVal = new string{ s };
		result->valueType = Type::String;
		return { result, line, col };
	} else {
		throwError(line, col);
		return { nullptr, line, col };
	}
}


JSON::Value JSON::parseBool(istream& in, int line, int col) {
	bool inBool = false;
	bool checkRead = false;
	string s;
	bool boolValue = false;
	while (!in.eof()) {
		char c = in.get();
		col++;
		if (c == '\n') {
			line++;
			col = 0;
		}
		if (c == ' ' || c == '\n') {
			continue;
		} else {
			inBool = true;
		}
		if (inBool) {
			s.push_back(c);
			if (s.length() == 4 && s == "true") {
				boolValue = true;
				checkRead = true;
				break;
			} else if (s.length() == 5 && s == "false") {
				boolValue = false;
				checkRead = true;
				break;
			} else if (s.length() >= 5) {
				break;
			}
		}
	}
	if (checkRead) {
		JSON* result = new JSON();
		result->boolVal = new bool{ boolValue };
		result->valueType = Type::Bool;
		return { result, line, col };
	} else {
		throwError(line, col);
		return { nullptr, line, col };
	}
}

bool JSON::has(int index) {
	return valueType == Type::Array && index >= 0 && index <= (int)arrayVal->size();
}

bool JSON::has(string key) {
	return valueType == Type::Object && objectVal->count(key);
}

JSON* JSON::at(int x) {
	if (valueType == Type::Array) {
		return arrayVal->at(x);
	} else {
		return nullptr;
	}
}

JSON* JSON::at(string s) {
	if (valueType == Type::Object) {
		return objectVal->at(s);
	} else {
		return nullptr;
	}
}

const JSON::Object* JSON::getObject() {
	return objectVal;
}

const JSON::Array* JSON::getArray() {
	return arrayVal;
}

const string* JSON::getString() {
	return stringVal;
}

const int* JSON::getInt() {
	return intVal;
}

const bool* JSON::getBool() {
	return boolVal;
}

JSON::Type JSON::getValueType() {
	return valueType;
}

JSON::~JSON() {
	if (intVal != nullptr) delete intVal;
	if (stringVal != nullptr) delete stringVal;
	if (boolVal != nullptr) delete boolVal;
	if (objectVal != nullptr) {
		for (auto entry : *objectVal) {
			delete entry.second;
		}
		delete objectVal;
	}
	if (arrayVal != nullptr) {
		for (auto entry : *arrayVal) {
			delete entry;
		}
		delete arrayVal;
	}
}
