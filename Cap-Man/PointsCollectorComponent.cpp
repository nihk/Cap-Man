#include "PointsCollectorComponent.h"

PointsCollectorComponent::PointsCollectorComponent()
    : PointsCollectorComponent(0) {
}

PointsCollectorComponent::PointsCollectorComponent(int initialPoints)
    : mPoints(initialPoints) {
}

PointsCollectorComponent::~PointsCollectorComponent() {
}
