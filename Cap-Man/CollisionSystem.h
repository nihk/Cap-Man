#pragma once
#include "System.h"

class Map;

class CollisionSystem 
	: public System {
public:
	CollisionSystem(Manager& manager, Map& map);
	~CollisionSystem();

	void updateEntity(float delta, int entity) override;

private:
	Map& mMap;
};

