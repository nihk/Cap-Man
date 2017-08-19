#pragma once
#include "System.h"

class Map;

class SpeedChangedSystem 
	: public System {
public:
	SpeedChangedSystem(Manager& manager, Map& map);
	~SpeedChangedSystem();

	void updateEntity(float delta, int entity) override;

private:
	Map& mMap;
};

