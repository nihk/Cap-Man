#pragma once
#include "System.h"

class GhostEatenSystem 
	: public System {
public:
	GhostEatenSystem(Manager& manager);
	~GhostEatenSystem();

	void updateEntity(float delta, int entity) override;
};

