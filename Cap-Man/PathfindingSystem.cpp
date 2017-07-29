#include "PathfindingSystem.h"
#include "PhysicsComponent.h"
#include "AStarComponent.h"
#include "Manager.h"
#include "Map.h"
#include "PathGoalComponent.h"

PathfindingSystem::PathfindingSystem(Manager& manager, Map& map) 
		: System(manager)
		, mMap(map) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(AStarComponent::ID);
	insertRequiredComponent(DirectionInputComponent::ID);
	insertRequiredComponent(PathGoalComponent::ID);
}

PathfindingSystem::~PathfindingSystem() {
}

void PathfindingSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	AStarComponent& aStarComponent = mManager.getComponent<AStarComponent>(entity);
	DirectionInputComponent& directionInputComponent = mManager.getComponent<DirectionInputComponent>(entity);
	PathGoalComponent& pathGoalComponent = mManager.getComponent<PathGoalComponent>(entity);

	if (!pathGoalComponent.hasGoal()) {
		return;
	}

	Rect rect = physicsComponent.rect();
	Point current = rect.center();
	mMap.scalePixelsToUnits(current);
	Point goal = pathGoalComponent.goal();

	if (!aStarComponent.hasPath()) {
		aStarComponent.findPath(current, goal);
	}

	Point nextStep = aStarComponent.peekCurrentPathStep();

	// TODO: Resolve this workaround for a bug
	//if (!nextStep.isAdjacentToOrOn(current)) {
	//	aStarComponent.purgePath();
	//	aStarComponent.findPath(current, goal);
	//}

	if (current == nextStep) {
		aStarComponent.popNextPathStep();

		// Exhausted the path nodes; remove the goal
		if (!aStarComponent.hasPath()) {
			pathGoalComponent.removeGoal();
		} else {
			nextStep = aStarComponent.peekCurrentPathStep();
		}
	}

	if (current.x() + 1 == nextStep.x()) {
		directionInputComponent.setDirection(Directions::RIGHT);
	} else if (current.x() - 1 == nextStep.x()) {
		directionInputComponent.setDirection(Directions::LEFT);
	} else if (current.y() + 1 == nextStep.y()) {
		directionInputComponent.setDirection(Directions::DOWN);
	} else if (current.y() - 1 == nextStep.y()) {
		directionInputComponent.setDirection(Directions::UP);
	}
}
