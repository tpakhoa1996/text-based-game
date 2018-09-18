#include "stdafx.h"
#include "Investigator.h"


Map::Map(JSON* config) {
	areas = new AreaVec();
	const JSON::Array* areasConfig = config->at("areas")->getArray();
	for (int i = 0; i < (int) areasConfig->size(); i++) {
		areas->push_back(new Area(areasConfig->at(i)));
	}
	const JSON::Array* doorsConfig = config->at("doors")->getArray();
	for (int i = 0; i < (int) doorsConfig->size(); i++) {
		doors.push_back({
			{*doorsConfig->at(i)->at(0)->getInt(), *doorsConfig->at(i)->at(1)->getInt()},
			{*doorsConfig->at(i)->at(2)->getInt(), *doorsConfig->at(i)->at(3)->getInt()}
		});
	}
	draw();
	createAreaMarker();
	createConnectionBetweenAreas();
}

void Map::createConnectionBetweenAreas() {
	for (int i = 0; i < (int)doors.size(); i++) {
		Door door = doors[i];
		pair<Area*, Area*> connectedAreas = { nullptr, nullptr };
		for (int e = 0; e < (int)areas->size(); e++) {
			const Area::VerticesVec* vertices = areas->at(e)->getVertices();
			for (int i = 0; i + 1 < (int)vertices->size(); i++) {
				const helper::Point *u = vertices->at(i), *v = vertices->at(i + 1);
				if (v->first < u->first || v->second < u->second) {
					swap(u, v);
				}
				if (u->first <= door.first.first && u->second <= door.first.second &&
					v->first >= door.second.first && v->second >= door.second.second) {
					if (connectedAreas.first == nullptr) {
						connectedAreas.first = areas->at(e);
					}
					else {
						connectedAreas.second = areas->at(e);
					}
					break;
				}
			}
			if (connectedAreas.second != nullptr) {
				break;
			}
		}

		if (connectedAreas.first != nullptr && connectedAreas.second != nullptr) {
			connectedAreas.first->connect(connectedAreas.second);
			connectedAreas.second->connect(connectedAreas.first);
		}
	}
}

void Map::draw() {
	if (!mapCanvas.empty()) {
		for (auto row : mapCanvas) {
			delete row;
		}
		mapCanvas.clear();
	}
	for (int i = 0; i < (int)areas->size(); i++) {
		drawAreaOnCanvas(areas->at(i), i);
	}
	for (int i = 0; i < (int)doors.size(); i++) {
		drawDoor(doors[i]);
	}
	formatCanvas();
}

void Map::drawAreaOnCanvas(Area* area, int areaIndex) {
	const Area::VerticesVec* vertices = area->getVertices();
	int labelVertex = -1, maxLabelArea = 0;
	for (int i = 0; i < (int) vertices->size(); i++) {

		const helper::Point *u = vertices->at(i), *v = vertices->at((i + 1) % vertices->size());

		// identify triangle with max area for labeling
		const helper::Point *c = vertices->at((i + 2) % vertices->size());
		int len1 = abs(v->first - u->first) + abs(v->second - u->second);
		int len2 = abs(v->first - c->first) + abs(v->second - c->second);
		int area = len1 * len2;
		if (area > maxLabelArea) {
			maxLabelArea = area;
			labelVertex = i;
		}

		// drawing each edge
		if (v->first < u->first || v->second < u->second) {
			swap(u, v);
		}
		int row = u->first, col = u->second;
		while (1) {
			helper::Point tempVertex(row, col);
			if ((int)mapCanvas.size() <= row) {
				mapCanvas.resize(row + 1, nullptr);
				mapCanvas[row] = new MapCanvasRow();
			}
			if ((int)mapCanvas[row]->size() <= col) {
				mapCanvas[row]->resize(col + 1, ' ');
			}
			if (tempVertex == *u || tempVertex == *v) {
				mapCanvas[row]->at(col) = '+';
			}
			else {
				char symbol = 0;
				if (v->second > col) {
					symbol = '-';
				}
				else if (v->first > row) {
					symbol = '|';
				}
				if (mapCanvas[row]->at(col) != ' ' && mapCanvas[row]->at(col) != symbol) {
					mapCanvas[row]->at(col) = '+';
				}
				else {
					mapCanvas[row]->at(col) = symbol;
				}
			}
			if (row < v->first) {
				row++;
			}
			if (col < v->second) {
				col++;
			}
			if (tempVertex == *v) {
				break;
			}
		}
	}

	for (int i = 0; i < (int)mapCanvas.size(); i++) {
		if (mapCanvas[i] == nullptr) {
			mapCanvas[i] = new MapCanvasRow();
		}
	}

	if (labelVertex >= 0) {
		helper::Point labelPlace = { 0, 0 };
		for (int d = 0; d < 3; d++) {
			int index = (labelVertex + d) % vertices->size();
			labelPlace.first += vertices->at(index)->first;
			labelPlace.second += vertices->at(index)->second;
		}
		labelPlace.first /= 3;
		labelPlace.second /= 3;
		mapCanvas[labelPlace.first]->at(labelPlace.second) = char(areaIndex + 48);
	}
}

void Map::drawDoor(Door door) {
	helper::Point u = door.first, v = door.second;
	if (v.first < u.first || v.second < u.second) {
		swap(u, v);
	}
	int row = u.first, col = u.second;
	while (row != v.first || col != v.second) {
		mapCanvas[row]->at(col) = '~';
		if (row < v.first) {
			row++;
		}
		if (col < v.second) {
			col++;
		}
	}
}

void Map::formatCanvas() {
	int minLeftSymbol = 0, minNonEmptyRow = 0;
	for (int i = 0; i < (int)mapCanvas.size(); i++) {
		int maxRightSymbol = -1;
		for (int e = 0; e < (int)mapCanvas[i]->size(); e++) {
			if (mapCanvas[i]->at(e) != ' ') {
				if (maxRightSymbol == 0) {
					minLeftSymbol = min(minLeftSymbol, e);
				}
				maxRightSymbol = e;
			}
		}
		mapCanvas[i]->resize(maxRightSymbol + 1);
		if (!mapCanvas[i]->empty()) {
			minNonEmptyRow = min(minNonEmptyRow, i);
		}
	}
	for (int i = 0; i < (int)mapCanvas.size() - minNonEmptyRow; i++) {
		mapCanvas[i] = mapCanvas[i + minNonEmptyRow];
		for (int e = 0; e < (int)mapCanvas[i]->size() - minLeftSymbol; e++) {
			mapCanvas[i]->at(e) = mapCanvas[i]->at(e + minLeftSymbol);
		}
		mapCanvas[i]->resize(mapCanvas[i]->size() - minLeftSymbol);
	}
	mapCanvas.resize(mapCanvas.size() - minNonEmptyRow);
}

void Map::createAreaMarker() {
	for (int i = 0; i < (int)mapCanvas.size(); i++) {
		areaCanvas.push_back(new AreaCanvasRow());
		areaCanvas[i]->resize(mapCanvas[i]->size(), -3);
	}

	for (int i = 0; i < (int)mapCanvas.size(); i++) {
		for (int e = 0; e < (int)mapCanvas[i]->size(); e++) {
			char symbol = mapCanvas[i]->at(e);
			if (symbol == '|' || symbol == '-' || symbol == '+') {
				areaCanvas[i]->at(e) = -2;
			} else if (symbol == '~') {
				areaCanvas[i]->at(e) = -1;
			}
		}
		cout << endl;
	}

	for (int i = 0; i < (int)mapCanvas.size(); i ++) {
		for (int e = 0; e < (int)mapCanvas[i]->size(); e++) {
			if (areaCanvas[i]->at(e) >= -1) {
				continue;
			}
			char symbol = mapCanvas[i]->at(e);
			if ('0' <= symbol && symbol <= '9') {
				int areaIndex = symbol - '0';
				queue<helper::Point> q;
				q.push({ i, e });
				while (!q.empty()) {
					helper::Point u = q.front();
					q.pop();
					for (auto d : helper::direction) {
						helper::Point v = { u.first + d.first, u.second + d.second };
						symbol = mapCanvas[v.first]->at(v.second);
						if (areaCanvas[v.first]->at(v.second) == -3) {
							areaCanvas[v.first]->at(v.second) = areaIndex;
							q.push(v);
						}
					}
				}
			}
		}
	}
}

string Map::toString(CharacterVec* characterList, Area* focusArea, bool labelRequired) {
	// create temporary canvas and remove area label
	Canvas<MapCanvasRow> temp = Canvas<MapCanvasRow>();
	for (int i = 0; i < (int)mapCanvas.size(); i++) {
		temp.push_back(new MapCanvasRow(mapCanvas[i]->size()));
		for (int e = 0; e < (int)mapCanvas[i]->size(); e++) {
			char symbol = mapCanvas[i]->at(e);
			if (!labelRequired && '0' <= symbol && symbol <= '9') {
				symbol = ' ';
			}
			temp[i]->at(e) = symbol;
		}
	}

	// mark characters onto the map
	if (characterList != nullptr) {
		for (auto character : *characterList) {
			helper::Point p = character->getPosition();
			if (!checkPointOnBorder(p) && !checkPointOutsideMap(p)) {
				if (focusArea != nullptr && character->getCurrentArea() != focusArea) {
					continue;
				}
				char symbol = temp[p.first]->at(p.second);
				temp[p.first]->at(p.second) = character->getMarker();
				if (symbol >= '0' && symbol <= '9') {
					int areaIndex = symbol - '0';
					queue<helper::Point> q;
					set<helper::Point> s;
					q.push({ p.first, p.second });
					s.insert(p);
					while (!q.empty()) {
						helper::Point u = q.front();
						q.pop();
						s.erase(u);
						if (temp[u.first]->at(u.second) == ' ') {
							temp[u.first]->at(u.second) = symbol;
							break;
						}
						for (auto d : helper::direction) {
							helper::Point v = { u.first + d.first, u.second + d.second };
							if (checkPointOutsideMap(v) || s.count(v) ||
								areaCanvas[v.first]->at(v.second) != areaIndex) {
								continue;
							}
							q.push(v);
						}
					}
				}
			}
		}
	}

	// focus an area
	if (focusArea != nullptr) {
		int areaIndex = -1;
		for (int i = 0; i < (int)areas->size(); i++) {
			if (areas->at(i) == focusArea) {
				areaIndex = i;
				break;
			}
		}

		for (int i = 0; i < (int)temp.size(); i++) {
			for (int e = 0; e < (int)temp[i]->size(); e++) {
				char symbol = temp[i]->at(e);
				int mark = areaCanvas[i]->at(e);
				if ((symbol == ' ') && (mark == areaIndex)) {
					temp[i]->at(e) = '.';
				}
			}
		}
	}

	string result = stringify(&temp);

	for (int i = 0; i < (int)temp.size(); i++) {
		delete temp[i];
	}
	
	return result;
}


string Map::stringify(MapCanvas *temp) {
	ostringstream output;
	for (int i = 0; i < (int)temp->size(); i++) {
		for (int e = 0; e < (int)temp->at(i)->size(); e++) {
			char symbol = temp->at(i)->at(e);
			char padding = ' ';
			if (e) {
				char preSymbol = temp->at(i)->at(e - 1);
				if ((symbol == '+' || symbol == '-') &&
					(preSymbol == '+' || preSymbol == '-')) {
					padding = '-';
				}
			}
			output << padding << symbol;
		}
		output << endl;
	}
	return output.str();
}

string Map::renderOveralMap(Character* mainCharacter) {
	CharacterVec* temp = new CharacterVec{ mainCharacter };
	string result = toString(temp, nullptr, true);
	ostringstream out;
	out << endl << endl;
	out << "List of area name according to their label on the map" << endl;
	for (int i = 0; i < (int)areas->size(); i++) {
		out << i << ": " << areas->at(i)->getName() << endl;
	}
	result += out.str();
	delete temp;
	return result;
}

string Map::renderPlayMap(CharacterVec* characterList, Area* focusArea) {
	return toString(characterList, focusArea, false);
}

bool Map::checkPointOnBorder(helper::Point p) {
	return (areaCanvas[p.first]->at(p.second) == -2);
}

bool Map::checkPointOnDoor(helper::Point p) {
	return (areaCanvas[p.first]->at(p.second) == -1);
}

bool Map::checkPointOutsideMap(helper::Point p) {
	bool check = false;
	if (p.first < 0 || p.second < 0) {
		check = true;
	} else if (p.first >= (int)areaCanvas.size()) {
		check = true;
	} else if (p.second >= (int)areaCanvas[p.first]->size()) {
		check = true;
	} else if (areaCanvas[p.first]->at(p.second) == -3) {
		check = true;
	}
	return check;
}


Area* Map::getAreaFromPoint(helper::Point p) {
	int areaIndex = areaCanvas[p.first]->at(p.second);
	Area* result = nullptr;
	if (areaIndex >= 0) {
		result = areas->at(areaIndex);
	}
	return result;
}

Map::~Map() {
	for (int i = 0; i < (int)mapCanvas.size(); i++) {
		delete mapCanvas[i];
		delete areaCanvas[i];
	}
	if (areas != nullptr) {
		for (int i = 0; i < (int)areas->size(); i++) {
			delete areas->at(i);
		}
		delete areas;
	}
}
