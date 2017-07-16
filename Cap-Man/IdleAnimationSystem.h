#pragma once

#include "System.h"

// A system for updating animations that aren't dependent on direction states
class IdleAnimationSystem
	: public System {
public:
	IdleAnimationSystem(Manager& manager);
	~IdleAnimationSystem();

	void updateEntity(float delta, int entity) override;
};

