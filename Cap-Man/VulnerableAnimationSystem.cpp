#include "VulnerableAnimationSystem.h"
#include "VulnerabilityComponent.h"
#include "GraphicsComponent.h"
#include "LastValidDirectionComponent.h"
#include "Manager.h"

VulnerableAnimationSystem::VulnerableAnimationSystem(Manager& manager) 
		: System(manager) {
	insertRequiredComponent(VulnerabilityComponent::ID);
	insertRequiredComponent(GraphicsComponent::ID);
}

VulnerableAnimationSystem::~VulnerableAnimationSystem() {
}

void VulnerableAnimationSystem::updateEntity(float delta, int entity) {
	GraphicsComponent& graphicsComponent = mManager.getComponent<GraphicsComponent>(entity);
	VulnerabilityComponent& vulnerabilityComponent = mManager.getComponent<VulnerabilityComponent>(entity);

	if (vulnerabilityComponent.isVulnerable()) {
		AnimationStates::AnimationState animationState;

		if (vulnerabilityComponent.timeRemainingVulnerable() <= GameConstants::GHOST_EXPIRING_ANIMATION_TIME) {
			animationState = AnimationStates::VULNERABLE_EXPIRING;
		} else {
			animationState = AnimationStates::VULNERABLE;
		}

		// The graphics component will have already passed a delta update from the DirectionAnimationSystem
		graphicsComponent.update(delta, animationState);
	}
}
