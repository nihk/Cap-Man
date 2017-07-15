#include "PathfindingSystem.h"
#include "PhysicsComponent.h"
#include "AStarComponent.h"
#include "Manager.h"
#include "Map.h"

PathfindingSystem::PathfindingSystem(Manager& manager, Map& map) 
		: System(manager)
		, mMap(map) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(AStarComponent::ID);
	insertRequiredComponent(DirectionInputComponent::ID);
}

PathfindingSystem::~PathfindingSystem() {
}

void PathfindingSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	AStarComponent& aStarComponent = mManager.getComponent<AStarComponent>(entity);
	DirectionInputComponent& directionInputComponent = mManager.getComponent<DirectionInputComponent>(entity);

	Rect rect = physicsComponent.rect();
	Point current = rect.center();
	mMap.scalePixelsToUnits(current);

	if (!aStarComponent.hasPath()) {
		Point goal(18, 20);
		aStarComponent.findPath(current, goal);
	} 

	Point nextStep = aStarComponent.peekCurrentPathStep();
	if (current == nextStep) {
		nextStep = aStarComponent.popNextPathStep();
	}

	if (current.x() < nextStep.x()) {
		directionInputComponent.setDirection(Directions::RIGHT);
	} else if (current.x() > nextStep.x()) {
		directionInputComponent.setDirection(Directions::LEFT);
	} else if (current.y() < nextStep.y()) {
		directionInputComponent.setDirection(Directions::DOWN);
	} else if (current.y() > nextStep.y()) {
		directionInputComponent.setDirection(Directions::UP);
	}
}
