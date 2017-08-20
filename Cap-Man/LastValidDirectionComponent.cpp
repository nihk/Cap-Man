#include "LastValidDirectionComponent.h"
#include "Map.h"

LastValidDirectionComponent::LastValidDirectionComponent()
    : LastValidDirectionComponent(Directions::NONE) {
}

LastValidDirectionComponent::LastValidDirectionComponent(Directions::Direction initialValidDirection)
    : mLastKnownValidDirection(initialValidDirection) {
}

LastValidDirectionComponent::~LastValidDirectionComponent() {
}
