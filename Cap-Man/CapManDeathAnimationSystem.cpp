#include "CapManDeathAnimationSystem.h"
#include "DeathComponent.h"
#include "GraphicsComponent.h"
#include "WinConditionComponent.h"
#include "Manager.h"
#include "AnimationGraphicsComponent.h"

CapManDeathAnimationSystem::CapManDeathAnimationSystem(Manager& manager) 
		: System(manager) {
	insertRequiredComponent(DeathComponent::ID);
	insertRequiredComponent(AnimationGraphicsComponent::ID);
	// Hack: I just added this required component so that only Cap-man will be updated within this system
	insertRequiredComponent(WinConditionComponent::ID);
}

CapManDeathAnimationSystem::~CapManDeathAnimationSystem() {
}

void CapManDeathAnimationSystem::updateEntity(float delta, int entity) {
	DeathComponent& deathComponent = mManager.getComponent<DeathComponent>(entity);
	AnimationGraphicsComponent& graphicsComponent = mManager.getComponent<AnimationGraphicsComponent>(entity);

	if (!deathComponent.isDead()) {
		return;
	}

	AnimationStates::AnimationState animationState = graphicsComponent.state();

	if (animationState != AnimationStates::DEATH) {
		graphicsComponent.resetAccumulatedTime(AnimationStates::DEATH);
	}

	graphicsComponent.update(delta, AnimationStates::DEATH);
}
