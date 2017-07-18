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
	AnimationStates::AnimationState animationState;

	bool halted = direction == Directions::NONE;

	switch (prevValidDirection) {
		case Directions::LEFT: {
			animationState = halted ? AnimationStates::STATIONARY_LEFT : AnimationStates::WALK_LEFT;
			break;
		}
		case Directions::RIGHT: {
			animationState = halted ? AnimationStates::STATIONARY_RIGHT : AnimationStates::WALK_RIGHT;
			break;
		}
		case Directions::UP: {
			animationState = halted ? AnimationStates::STATIONARY_UP : AnimationStates::WALK_UP;
			break;
		}
		case Directions::DOWN:  // Fall through
		default: {
			animationState = halted ? AnimationStates::STATIONARY_DOWN : AnimationStates::WALK_DOWN;
			break;
		}
	}

	graphicsComponent.update(delta, animationState);
}
