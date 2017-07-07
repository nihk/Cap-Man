#include "DirectionAnimationSystem.h"
#include "GraphicsComponent.h"
#include "Manager.h"
#include "LastValidDirectionComponent.h"

DirectionAnimationSystem::DirectionAnimationSystem(Manager& manager)
		: System(manager) {
	insertRequiredComponent(DirectionInputComponent::ID);
	insertRequiredComponent(LastValidDirectionComponent::ID);
	insertRequiredComponent(GraphicsComponent::ID);
}

DirectionAnimationSystem::~DirectionAnimationSystem() {
}

void DirectionAnimationSystem::updateEntity(float delta, int entity) {
	DirectionInputComponent& directionInputComponent = mManager.getComponent<DirectionInputComponent>(entity);
	LastValidDirectionComponent& lastValidDirectionComponent = mManager.getComponent<LastValidDirectionComponent>(entity);
	GraphicsComponent& graphicsComponent = mManager.getComponent<GraphicsComponent>(entity);

	Directions::Direction prevValidDirection = lastValidDirectionComponent.lastKnownValidDirection();
	Directions::Direction direction = directionInputComponent.direction();

	// If the current direction is NONE, then character is facing a wall,
	// so set the delta to 0.0f so the animation won't progress (it'll "freeze")
	// and draw the direction that was last valid
	// TODO: This is wonky logic and conflates direction with state
	if (direction == Directions::NONE) {
		delta = 0.0f;
	} 

	graphicsComponent.update(delta, prevValidDirection);
}
