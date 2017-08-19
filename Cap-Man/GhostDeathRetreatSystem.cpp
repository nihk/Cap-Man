#include "GhostDeathRetreatSystem.h"
#include "PhysicsComponent.h"
#include "RetreatUponDeathComponent.h"
#include "PathGoalComponent.h"
#include "Manager.h"
#include "DeathComponent.h"
#include "VulnerabilityComponent.h"
#include "VelocityComponent.h"
#include "AStarComponent.h"

GhostDeathRetreatSystem::GhostDeathRetreatSystem(Manager& manager, Map& map)
		: System(manager)
		, mMap(map) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(RetreatUponDeathComponent::ID);
	insertRequiredComponent(PathGoalComponent::ID);
	insertRequiredComponent(DeathComponent::ID);
	insertRequiredComponent(VulnerabilityComponent::ID);
	insertRequiredComponent(VelocityComponent::ID);
	insertRequiredComponent(AStarComponent::ID);
}

GhostDeathRetreatSystem::~GhostDeathRetreatSystem() {
}

void GhostDeathRetreatSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	RetreatUponDeathComponent& retreatUponDeathComponent = mManager.getComponent<RetreatUponDeathComponent>(entity);
	PathGoalComponent& pathGoalComponent = mManager.getComponent<PathGoalComponent>(entity);
	DeathComponent& deathComponent = mManager.getComponent<DeathComponent>(entity);
	VulnerabilityComponent& vulnerabilityComponent = mManager.getComponent<VulnerabilityComponent>(entity);
	VelocityComponent& velocityComponent = mManager.getComponent<VelocityComponent>(entity);
	AStarComponent& aStarComponent = mManager.getComponent<AStarComponent>(entity);

	if (!deathComponent.isDead()) {
		return;
	}

	Point home = retreatUponDeathComponent.home();
	Rect rect = physicsComponent.rect();
	Point center = rect.center();
	mMap.scalePixelsToUnits(center);

	// Reached the home, so undo the death state for the ghost
	if (center == home) {
		deathComponent.setDead(false);
		vulnerabilityComponent.reset();
		velocityComponent.setCurrentSpeed(velocityComponent.defaultSpeed());
		pathGoalComponent.removeGoal();
	}

	if (!pathGoalComponent.hasGoal() || pathGoalComponent.goal() != home) {
		pathGoalComponent.setGoal(home);
		aStarComponent.purgePath();
		aStarComponent.findPath(center, home);
	}
}
