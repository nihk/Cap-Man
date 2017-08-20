#include "IdleAnimationSystem.h"
#include "GraphicsComponent.h"
#include "IdleAnimationComponent.h"
#include "Manager.h"

IdleAnimationSystem::IdleAnimationSystem(Manager& manager) 
        : System(manager) {
    insertRequiredComponent(IdleAnimationComponent::ID);
    insertRequiredComponent(GraphicsComponent::ID);
}

IdleAnimationSystem::~IdleAnimationSystem() {
}

void IdleAnimationSystem::updateEntity(float delta, int entity) {
    IdleAnimationComponent& idleAnimationComponent = mManager.getComponent<IdleAnimationComponent>(entity);
    GraphicsComponent& graphicsComponent = mManager.getComponent<GraphicsComponent>(entity);
    graphicsComponent.update(delta, idleAnimationComponent.state());
}
