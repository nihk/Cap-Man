#include "DirectionAnimationSystem.h"
#include "GraphicsComponent.h"
#include "Manager.h"
#include "DirectionValidatorComponent.h"

DirectionAnimationSystem::DirectionAnimationSystem(Manager& manager)
		: System(manager) {
	insertRequiredComponent(DirectionInputComponent::ID);
	insertRequiredComponent(DirectionValidatorComponent::ID);
	insertRequiredComponent(GraphicsComponent::ID);
}

DirectionAnimationSystem::~DirectionAnimationSystem() {
}

void DirectionAnimationSystem::updateEntity(float delta, int entity) {
	DirectionInputComponent& directionInputComponent = mManager.getComponent<DirectionInputComponent>(entity);
	DirectionValidatorComponent& directionValidatorComponent = mManager.getComponent<DirectionValidatorComponent>(entity);
	GraphicsComponent& graphicsComponent = mManager.getComponent<GraphicsComponent>(entity);

	Directions::Direction prevValidDirection = directionValidatorComponent.lastKnownValidDirection();
	Directions::Direction direction = directionInputComponent.direction();
	if (direction == Directions::NONE) {
		delta = 0.0f;
	}
	graphicsComponent.update(delta, prevValidDirection);
}
