#pragma once
#include "System.h"

class CapManDeathAnimationSystem 
	: public System {
public:
	CapManDeathAnimationSystem(Manager& manager);
	~CapManDeathAnimationSystem();

	void updateEntity(float delta, int entity) override;
};

