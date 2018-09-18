#pragma once
#include "ItemGroupContext.h"
class ItemAction : public Action {
public:
	enum class ActionState {
		Examine, Pick, Drop
	};
	ItemAction(Investigator*, Item*, ItemGroupContext*);
	~ItemAction();

	// Inherited via Action
	virtual bool action() override;
	virtual string toString() override;
	virtual Action * clone() override;

	void updateState();

private:
	Investigator* mainCharacter = nullptr;
	ItemGroupContext* context;
	Item* item = nullptr;
	ActionState state;
};

