#pragma once

#include "Component.h"
#include "DirectionInputComponent.h"

class Point;
class Map;

class LastValidDirectionComponent 
	: public Component<LastValidDirectionComponent> {
public:
	LastValidDirectionComponent();
	~LastValidDirectionComponent();

	Directions::Direction lastKnownValidDirection() const { return mLastKnownValidDirection; }
	void setLastKnownValidDirection(Directions::Direction direction) { mLastKnownValidDirection = direction; }
	void invalidate() { setLastKnownValidDirection(Directions::NONE); }

private:
	Directions::Direction mLastKnownValidDirection;
};

