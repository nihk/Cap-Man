#pragma once
#include "System.h"

class SpeedSystem 
	: public System {
public:
	SpeedSystem(Manager& manager);
	~SpeedSystem();

	void updateEntity(float delta, int entity) override;
};

