#include "PseudoRandomDirectionSystem.h"
#include "Manager.h"
#include "PhysicsComponent.h"
#include <iostream>
#include "PathGoalComponent.h"
#include "AStarComponent.h"

PseudoRandomDirectionSystem::PseudoRandomDirectionSystem(Manager& manager, Map& map) 
        : System(manager)
        , mMap(map) {
    insertRequiredComponent(PathGoalComponent::ID);
    insertRequiredComponent(PhysicsComponent::ID);
    insertRequiredComponent(DirectionInputComponent::ID);
}

PseudoRandomDirectionSystem::~PseudoRandomDirectionSystem() {
}

void PseudoRandomDirectionSystem::updateEntity(float delta, int entity) {
    PathGoalComponent& pathGoalComponent = mManager.getComponent<PathGoalComponent>(entity);
    PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
    DirectionInputComponent& directionInputComponent = mManager.getComponent<DirectionInputComponent>(entity);

    if (pathGoalComponent.hasGoal() 
            && directionInputComponent.direction() != Directions::NONE) {
        return;
    }

    Rect rect = physicsComponent.rect();
    Point center = rect.center();
    mMap.scalePixelsToUnits(center);

    const std::vector<int>& navigableIndices = mMap.navigableIndices();
    bool scaleUp = false;
    Point randomPoint;

    do {
        int randomIndex = rand() % navigableIndices.size();
        int randomTile = navigableIndices.at(randomIndex);
        randomPoint = mMap.mapLocation(randomTile, scaleUp);
    } while (randomPoint == center);

    pathGoalComponent.setGoal(randomPoint);
}
