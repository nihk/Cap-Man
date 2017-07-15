#pragma once

#include "System.h"
#include "DirectionInputComponent.h"
#include "Rect.h"

class Map;

// TODO: Rename to WallHuggingSystem
class WallPathingSystem 
	: public System {
public:
	WallPathingSystem(Manager& manager, Map& map);
	~WallPathingSystem();

	void updateEntity(float delta, int entity) override;

private:
	static bool isElementWallOrInvalid(int element);
	void getNeighbourElementsByDirection(Directions::Direction direction, Rect rect, int& neighbourElement1, int& neighbourElement2) const;

	Map& mMap;
};

