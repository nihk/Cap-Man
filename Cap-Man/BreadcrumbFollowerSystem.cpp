#include "BreadcrumbFollowerSystem.h"
#include "PhysicsComponent.h"
#include "BreadcrumbFollowerComponent.h"
#include "Manager.h"
#include "BreadcrumbTrailComponent.h"
#include "Map.h"
#include <iostream>
#include "VulnerabilityComponent.h"
#include "VelocityComponent.h"
#include "AStarComponent.h"
#include "PathGoalComponent.h"

BreadcrumbFollowerSystem::BreadcrumbFollowerSystem(Manager& manager, Map& map) 
		: System(manager)
		, mMap(map) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(BreadcrumbFollowerComponent::ID);
	insertRequiredComponent(DirectionInputComponent::ID);
	insertRequiredComponent(VulnerabilityComponent::ID);
	insertRequiredComponent(VelocityComponent::ID);
	insertRequiredComponent(AStarComponent::ID);
	insertRequiredComponent(PathGoalComponent::ID);
}

BreadcrumbFollowerSystem::~BreadcrumbFollowerSystem() {
}

void BreadcrumbFollowerSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	BreadcrumbFollowerComponent& followerComponent = mManager.getComponent<BreadcrumbFollowerComponent>(entity);
	DirectionInputComponent& directionComponent = mManager.getComponent<DirectionInputComponent>(entity);
	VulnerabilityComponent& vulnerabilityComponent = mManager.getComponent<VulnerabilityComponent>(entity);
	VelocityComponent& velocityComponent = mManager.getComponent<VelocityComponent>(entity);
	AStarComponent& aStarComponent = mManager.getComponent<AStarComponent>(entity);
	PathGoalComponent& pathGoalComponent = mManager.getComponent<PathGoalComponent>(entity);

	vulnerabilityComponent.update(delta);

	int entityToFollow = followerComponent.entityToFollow();

	auto& trailStore = mManager.getComponentStore<BreadcrumbTrailComponent>();
	if (!trailStore.hasComponent(entityToFollow)) {
		std::cout << "Error: Breadcrumb trail component entity not found." << std::endl;
		return;
	}
	BreadcrumbTrailComponent& trailComponent = trailStore.getComponent(entityToFollow);

	Rect rect = physicsComponent.rect();
	Point center = rect.center();
	mMap.scalePixelsToUnits(center);

	// If the ghosts are vulnerable, don't follow capman. Originally I tried going to the
	// previous breadcrumb rather than the next, but this got wonky when the ghost
	// reached the "last" breadcrumb: once it was done "following" it would go in a 
	// pseudo random direction that could be the breadcrumb trail, so it would then
	// just revert back to the last breadcrumb over and over.
	if (trailComponent.hasBreadcrumb(center)
			&& vulnerabilityComponent.isVulnerable()
			&& pathGoalComponent.hasGoal()) {
		Point goal = pathGoalComponent.goal();
		if (aStarComponent.hasPath()) {
			Point nextStep = aStarComponent.peekCurrentPathStep();
			if (!center.isAdjacentToOrOn(nextStep)) {
				aStarComponent.purgePath();
				aStarComponent.findPath(center, goal);
			}
		}
	} else {
		Point nextBreadcrumb = trailComponent.nextBreadcrumb(center);

		Directions::Direction nextDir = nextDirection(center, nextBreadcrumb);

		// If the direction was NONE, just keep going in that same direction, then
		if (nextDir != Directions::NONE) {
			directionComponent.setDirection(nextDir);
		}
	}
}

Directions::Direction BreadcrumbFollowerSystem::nextDirection(const Point& current, const Point& dest) {
	// Only check contiguous points. Teleporters will otherwise make the follower confused
	// when a destination point is somewhere far away on the map
	if (current.x() + 1 == dest.x()) {
		return Directions::RIGHT;
	} 
	if (current.x() - 1 == dest.x()) {
		return Directions::LEFT;
	} 
	if (current.y() + 1 == dest.y()) {
		return Directions::DOWN;
	} 
	if (current.y() - 1 == dest.y()) {
		return Directions::UP;
	} 

	return Directions::NONE;
}
