#pragma once
#include "System.h"

class GhostDeathAnimationSystem 
	: public System {
public:
	GhostDeathAnimationSystem(Manager& manager);
	~GhostDeathAnimationSystem();

	void updateEntity(float delta, int entity) override;
};

