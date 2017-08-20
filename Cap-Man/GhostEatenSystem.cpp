#include "GhostEatenSystem.h"
#include "DeathComponent.h"
#include "VulnerabilityComponent.h"
#include "PhysicsComponent.h"
#include "Manager.h"
#include "EatableComponent.h"
#include "VelocityComponent.h"
#include "PointsCollectorComponent.h"
#include "SpeedChangeWatcherComponent.h"
#include "PauseComponent.h"
#include "PointsComboComponent.h"

GhostEatenSystem::GhostEatenSystem(Manager& manager, int& pauseEntity) 
		: System(manager)
		, mPauseEntity(pauseEntity) {
	insertRequiredComponent(DeathComponent::ID);
	insertRequiredComponent(VulnerabilityComponent::ID);
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(EatableComponent::ID);
	insertRequiredComponent(VelocityComponent::ID);
	insertRequiredComponent(SpeedChangeWatcherComponent::ID);
}

GhostEatenSystem::~GhostEatenSystem() {
}

void GhostEatenSystem::updateEntity(float delta, int entity) {
	DeathComponent& deathComponent = mManager.getComponent<DeathComponent>(entity);
	VulnerabilityComponent& vulnerabilityComponent = mManager.getComponent<VulnerabilityComponent>(entity);
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	EatableComponent& eatableComponent = mManager.getComponent<EatableComponent>(entity);
	VelocityComponent& velocityComponent = mManager.getComponent<VelocityComponent>(entity);
	SpeedChangeWatcherComponent& speedChangeWatcherComponent = mManager.getComponent<SpeedChangeWatcherComponent>(entity);

	if (!vulnerabilityComponent.isVulnerable() || deathComponent.isDead()) {
		return;
	}

	int eater = eatableComponent.eaterEntity();
	PhysicsComponent& eaterPhyicsComponent = mManager.getComponent<PhysicsComponent>(eater);
	PointsCollectorComponent& pointsCollectorComponent = mManager.getComponent<PointsCollectorComponent>(eater);
	PointsComboComponent& pointsComboComponent = mManager.getComponent<PointsComboComponent>(eater);
	Point eaterCenter = eaterPhyicsComponent.rect().center();

	Rect rect = physicsComponent.rect();
	if (rect.containsPoint(eaterCenter)) {
		PauseComponent& pauseComponent = mManager.getComponent<PauseComponent>(mPauseEntity);
		pauseComponent.pause(GameConstants::GHOST_EATEN_PAUSE_DURATION);
		eatableComponent.setEaten(true);
		deathComponent.setDead(true);
		velocityComponent.setCurrentSpeed(velocityComponent.doubleSpeed());
		speedChangeWatcherComponent.setSpeedChanged(true);

		int combo = pointsComboComponent.currentCombo();

		switch (combo) {
			case 1: eatableComponent.setEatenPointsAnimationState(AnimationStates::EATEN_200); break;
			case 2: eatableComponent.setEatenPointsAnimationState(AnimationStates::EATEN_400); break;
			case 4: eatableComponent.setEatenPointsAnimationState(AnimationStates::EATEN_800); break;
			case 8: eatableComponent.setEatenPointsAnimationState(AnimationStates::EATEN_1600); break;
			default: eatableComponent.setEatenPointsAnimationState(AnimationStates::EATEN_200); break;
		}

		pointsCollectorComponent.addPoints(GameConstants::EAT_GHOST_POINTS * combo);
		pointsComboComponent.addCombo();
	}
}
