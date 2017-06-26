#include "DirectionAnimationSystem.h"
#include "GraphicsComponent.h"
#include "DirectionInputComponent.h"
#include "Manager.h"

DirectionAnimationSystem::DirectionAnimationSystem(Manager& manager)
		: System(manager) {
	insertRequiredComponent(DirectionInputComponent::ID);
	insertRequiredComponent(GraphicsComponent::ID);
}

DirectionAnimationSystem::~DirectionAnimationSystem() {
}

void DirectionAnimationSystem::updateEntity(float delta, int entity) {
	DirectionInputComponent& directionInputComponent = mManager.getComponent<DirectionInputComponent>(entity);
	GraphicsComponent& graphicsComponent = mManager.getComponent<GraphicsComponent>(entity);

	Directions::Direction direction = directionInputComponent.direction();
	graphicsComponent.update(delta, direction);
}
