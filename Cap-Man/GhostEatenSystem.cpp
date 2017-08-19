#include "GhostEatenSystem.h"
#include "DeathComponent.h"
#include "VulnerabilityComponent.h"
#include "PhysicsComponent.h"
#include "Manager.h"
#include "EatableComponent.h"
#include "VelocityComponent.h"
#include "PointsCollectorComponent.h"
#include "SpeedChangeWatcherComponent.h"

GhostEatenSystem::GhostEatenSystem(Manager& manager) 
		: System(manager) {
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
	Point eaterCenter = eaterPhyicsComponent.rect().center();

	Rect rect = physicsComponent.rect();
	if (rect.containsPoint(eaterCenter)) {
		deathComponent.setDead(true);
		velocityComponent.setCurrentSpeed(/* velocityComponent.defaultSpeed() */ velocityComponent.doubleSpeed());
		speedChangeWatcherComponent.setSpeedChanged(true);
		pointsCollectorComponent.addPoints(GameConstants::EAT_GHOST_POINTS);
	}
}
