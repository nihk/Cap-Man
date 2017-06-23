#pragma once

#include "System.h"

class WallPathingSystem 
	: public System {
public:
	WallPathingSystem(Manager& manager);
	~WallPathingSystem();

	void updateEntity(float delta, int entity) override;
};

