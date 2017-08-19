#include "GhostDeathAnimationSystem.h"
#include "DeathComponent.h"
#include "GraphicsComponent.h"
#include "LastValidDirectionComponent.h"
#include "Manager.h"
#include "EatableComponent.h"

GhostDeathAnimationSystem::GhostDeathAnimationSystem(Manager& manager)
		: System(manager) {
	insertRequiredComponent(DeathComponent::ID);
	insertRequiredComponent(GraphicsComponent::ID);
	insertRequiredComponent(DirectionInputComponent::ID);
	insertRequiredComponent(LastValidDirectionComponent::ID);
	insertRequiredComponent(EatableComponent::ID);
}

GhostDeathAnimationSystem::~GhostDeathAnimationSystem() {
}

void GhostDeathAnimationSystem::updateEntity(float delta, int entity) {
	DeathComponent& deathComponent = mManager.getComponent<DeathComponent>(entity);
	LastValidDirectionComponent& lastValidDirectionComponent = mManager.getComponent<LastValidDirectionComponent>(entity);
	GraphicsComponent& graphicsComponent = mManager.getComponent<GraphicsComponent>(entity);
	EatableComponent& eatableComponent = mManager.getComponent<EatableComponent>(entity);

	eatableComponent.update(delta);

	if (!deathComponent.isDead()) {
		return;
	}

	AnimationStates::AnimationState animationState;

	if (eatableComponent.isEaten()) {
		animationState = eatableComponent.eatenPointsAnimationState();
	} else {
		Directions::Direction prevValidDirection = lastValidDirectionComponent.lastKnownValidDirection();

		switch (prevValidDirection) {
			case Directions::LEFT: {
				animationState = AnimationStates::DEATH_LEFT;
				break;
			}
			case Directions::RIGHT: {
				animationState = AnimationStates::DEATH_RIGHT;
				break;
			}
			case Directions::UP: {
				animationState = AnimationStates::DEATH_UP;
				break;
			}
			case Directions::DOWN:  // Fall through
			default: {
				animationState = AnimationStates::DEATH_DOWN;
				break;
			}
		}
	}

	graphicsComponent.update(delta, animationState);
}