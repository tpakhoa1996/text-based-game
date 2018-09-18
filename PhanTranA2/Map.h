#pragma once
#include "common.h"
#include "Area.h"
#include "Character.h"
#include "JSON.h"

class Map
{
public:
	using MapCanvasRow = vector<char>;
	using AreaCanvasRow = vector<int>;
	template<class CanvasRow>
	using Canvas = vector<CanvasRow*>;
	using MapCanvas = Canvas<MapCanvasRow>;
	using AreaCanvas = Canvas<AreaCanvasRow>;
	using AreaVec = vector<Area*>;
	using Door = pair<helper::Point, helper::Point>;
	using DoorVec = vector<Door>;
	using CharacterVec = vector<Character*>;

	Map(JSON*);

	bool checkPointOnBorder(helper::Point);
	bool checkPointOnDoor(helper::Point);
	bool checkPointOutsideMap(helper::Point);
	Area* getAreaFromPoint(helper::Point);

	string renderOveralMap(Character*);
	string renderPlayMap(CharacterVec*, Area*);

	~Map();

private:
	AreaVec *areas = nullptr;
	MapCanvas mapCanvas;
	DoorVec doors;
	AreaCanvas areaCanvas;

	void draw();
	void drawAreaOnCanvas(Area*, int);
	void drawDoor(Door);
	void createConnectionBetweenAreas();
	void formatCanvas();
	void createAreaMarker();
	string stringify(MapCanvas*);
	string toString(CharacterVec*, Area*, bool);
};