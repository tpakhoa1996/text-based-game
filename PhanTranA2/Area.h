#pragma once
#include "common.h"
#include "Item.h"
#include "JSON.h"
#include "ItemContainer.h"

class Area : public ItemContainer {
public:
	using VerticesVec = vector<const helper::Point*>;
	using AreaVec = vector<const Area*>;
	using ItemSet = set<Item*>;

	Area(JSON*);

	const VerticesVec* getVertices() const;
	string getName() const;

	bool addItem(Item*) override;
	bool removeItem(Item*) override;
	bool hasItem(Item*) override;
	ItemVec getItems() override;

	void connect(Area*);

	const AreaVec* getConnectedArea();

	~Area();
private:
	VerticesVec *vertices = nullptr;
	AreaVec *connectedAreas = nullptr;
	ItemSet items;
	string name, description;
};