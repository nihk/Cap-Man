#pragma once

#include "Component.h"
#include "DirectionInputComponent.h"

class Point;
class Map;

class DirectionValidatorComponent 
	: public Component<DirectionValidatorComponent> {
public:
	DirectionValidatorComponent();
	~DirectionValidatorComponent();

	Directions::Direction lastKnownValidDirection() const { return mLastKnownValidDirection; }
	void setLastKnownValidDirection(Directions::Direction direction) { mLastKnownValidDirection = direction; }

private:
	Directions::Direction mLastKnownValidDirection;
};

