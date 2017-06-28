#include "GhostDirectionInputComponent.h"

GhostDirectionInputComponent::GhostDirectionInputComponent(Map& map)
	: mMap(map) {
}

GhostDirectionInputComponent::~GhostDirectionInputComponent() {
}

Directions::Direction GhostDirectionInputComponent::direction() {
	// TODO
	return Directions::NONE;
}
