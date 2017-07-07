#include "DirectionInputComponent.h"

DirectionInputComponent::DirectionInputComponent() 
	: DirectionInputComponent(Directions::NONE) {
}

DirectionInputComponent::DirectionInputComponent(Directions::Direction startingDirection)
	: mDirection(startingDirection) {
}

DirectionInputComponent::~DirectionInputComponent() {
}
