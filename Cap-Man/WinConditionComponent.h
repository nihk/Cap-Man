#pragma once
#include "Component.h"

class WinConditionComponent 
	: public Component<WinConditionComponent> {
public:
	WinConditionComponent();
	~WinConditionComponent();

	bool hasWon() const { return mHasWon; }
	void reset();
	void setWon();
	int numGamesWon() const { return mNumGamesWon; }
	void nextRound();

private:
	bool mHasWon;
	int mNumGamesWon;
};

