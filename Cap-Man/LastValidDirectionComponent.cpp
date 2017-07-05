#include "LastValidDirectionComponent.h"
#include "Map.h"

LastValidDirectionComponent::LastValidDirectionComponent()
	// TODO: Rethink this once the conflation of direction and animation is resolved
	: mLastKnownValidDirection(Directions::LEFT) {
}

LastValidDirectionComponent::~LastValidDirectionComponent() {
}