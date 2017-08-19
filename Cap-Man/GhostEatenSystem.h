#pragma once
#include "System.h"

class GhostEatenSystem 
	: public System {
public:
	GhostEatenSystem(Manager& manager, int& pauseEntity);
	~GhostEatenSystem();

	void updateEntity(float delta, int entity) override;

private:
	int& mPauseEntity;
	int mEatenMultiplier;
};

