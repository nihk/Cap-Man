#include "SpeedSystem.h"
#include "VelocityComponent.h"
#include "Manager.h"
#include "DirectionInputComponent.h"

SpeedSystem::SpeedSystem(Manager& manager)
        : System(manager) {
    insertRequiredComponent(DirectionInputComponent::ID);
    insertRequiredComponent(VelocityComponent::ID);
}

SpeedSystem::~SpeedSystem() {
}

void SpeedSystem::updateEntity(float delta, int entity) {
    DirectionInputComponent& inputComponent = mManager.getComponent<DirectionInputComponent>(entity);
    VelocityComponent& velocityComponent = mManager.getComponent<VelocityComponent>(entity);

    Directions::Direction direction = inputComponent.direction();
    velocityComponent.setVelocityFromDirection(direction);
}
