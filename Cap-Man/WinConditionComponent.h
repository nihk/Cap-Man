#pragma once
#include "Component.h"

class WinConditionComponent 
	: public Component<WinConditionComponent> {
public:
	WinConditionComponent();
	~WinConditionComponent();

	bool hasWon() const { return mHasWon; }
	void setWon(bool hasWon) { mHasWon = hasWon; }

private:
	bool mHasWon;
};

