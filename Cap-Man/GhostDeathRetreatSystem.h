#pragma once

#include "System.h"
class Manager;

class GhostDeathRetreatSystem 
	: public System {
public:
	GhostDeathRetreatSystem(Manager& manager);
	~GhostDeathRetreatSystem();

	void updateEntity(float delta, int entity) override;
};

