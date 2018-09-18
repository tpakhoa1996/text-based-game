#pragma once
class JSON {
public:
	using Object = unordered_map<string, JSON*>;
	using Array = vector<JSON*>;
	using NextValue = tuple<JSON*, char, int, int>;
	using Value = tuple<JSON*, int, int>;
	enum class Type {
		Array,
		Object,
		String,
		Int,
		Bool,
		None
	};
	JSON();
	~JSON();
	static JSON* read(istream&);
	JSON* at(int);
	JSON* at(string);
	bool has(int);
	bool has(string);
	const Object* getObject();
	const Array* getArray();
	const int* getInt();
	const string* getString();
	const bool* getBool();
	Type  getValueType();
private:
	Type valueType = Type::None;

	int *intVal = nullptr;
	string *stringVal = nullptr;
	bool *boolVal = nullptr;
	Object *objectVal = nullptr;
	Array *arrayVal = nullptr;

	static Value parseObject(istream&, int, int);
	static Value parseArray(istream&, int, int);
	static Value parseString(istream&, int, int);
	static Value parseInt(istream&, int, int);
	static Value parseBool(istream&, int, int);
	static NextValue readNextValue(istream&, int, int);
	static void throwError(int, int);
};