#pragma once
// input/output libaries
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <iomanip>

// standard libaries
// container libaries
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>

// other libaries
#include <algorithm>
#include <utility>
#include <tuple>
#include <cctype>
#include <random>
#include <chrono>
#include <regex>

using namespace std;

namespace helper {
	using Point = pair<int, int>;
	using Vector = pair<int, int>;
	const Vector direction[4] = {
		{-1, 0}, {0, 1}, {1, 0}, {0, -1}
	};

	enum class Direction {
		Up, Right, Down, Left
	};

	string trim(string);
}