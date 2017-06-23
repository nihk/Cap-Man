#pragma once

#include "Component.h"
#include "DirectionInputComponent.h"

class WallPathingComponent 
	: public Component<WallPathingComponent> {
public:
	WallPathingComponent();
	~WallPathingComponent();

	Directions::Direction lastKnownValidDirection() const { return mLastKnownValidDirection; }
	void setLastKnownValidDirection(Directions::Direction direction) { mLastKnownValidDirection = direction; }

private:
	Directions::Direction mLastKnownValidDirection;
};

