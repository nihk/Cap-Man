#pragma once
#include "Component.h"
#include "Constants.h"

class DirectionInputComponent
	: public Component<DirectionInputComponent> {
public:
	DirectionInputComponent() = default;
	~DirectionInputComponent() = default;

	virtual Directions::Direction direction() { return Directions::NONE; }
};

