#pragma once
#include "System.h"

class PowerupMonitoringSystem 
	: public System {
public:
	PowerupMonitoringSystem(Manager& manager);
	~PowerupMonitoringSystem();

	void updateEntity(float delta, int entity) override;
};

