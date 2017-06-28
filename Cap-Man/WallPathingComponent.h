#pragma once

#include "Component.h"
#include "DirectionInputComponent.h"

class Map;

class WallPathingComponent 
	: public Component<WallPathingComponent> {
public:
	WallPathingComponent(Map& map);
	WallPathingComponent(const WallPathingComponent& other);
	~WallPathingComponent();

	WallPathingComponent& operator=(const WallPathingComponent& other);

	Directions::Direction lastKnownValidDirection() const { return mLastKnownValidDirection; }
	void setLastKnownValidDirection(Directions::Direction direction) { mLastKnownValidDirection = direction; }

private:
	Directions::Direction mLastKnownValidDirection;
	Map& mMap;
};

