#pragma once
#include "System.h"

class VulnerableAnimationSystem 
	: public System {
public:
	VulnerableAnimationSystem(Manager& manager);
	~VulnerableAnimationSystem();

	void updateEntity(float delta, int entity) override;
};

