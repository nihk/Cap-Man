#include "WallPathingSystem.h"
#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "LastValidDirectionComponent.h"
#include "Manager.h"
#include "Map.h"

WallPathingSystem::WallPathingSystem(Manager& manager, Map& map)
		: System(manager)
		, mMap(map) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(VelocityComponent::ID);
	insertRequiredComponent(LastValidDirectionComponent::ID);
	insertRequiredComponent(DirectionInputComponent::ID);
}

WallPathingSystem::~WallPathingSystem() {
}

void WallPathingSystem::updateEntity(float delta, int entity) {
	DirectionInputComponent& directionInputComponent = mManager.getComponent<DirectionInputComponent>(entity);
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	LastValidDirectionComponent& lastValidDirectionComponent = mManager.getComponent<LastValidDirectionComponent>(entity);
	VelocityComponent& velocityComponent = mManager.getComponent<VelocityComponent>(entity);

	// Hit a wall
	if (!velocityComponent.isMoving()) {
		return;
	}

	int direction = directionInputComponent.direction();
	Rect rect = physicsComponent.rect();

	int neighbourElement1;
	int neighbourElement2;

	getNeighbourElementsByDirection(direction, rect, neighbourElement1, neighbourElement2);

	// Current direction will hit a wall, so keep going in the last known valid one instead
	if (isElementWallOrInvalid(neighbourElement1)
			|| isElementWallOrInvalid(neighbourElement2)) {
		Directions::Direction lastKnownValidDirection = lastValidDirectionComponent.lastKnownValidDirection();

		int prevValidDirectionNeighbourElement1;
		int prevValidDirectionNeighbourElement2;

		getNeighbourElementsByDirection(lastKnownValidDirection, rect, prevValidDirectionNeighbourElement1, prevValidDirectionNeighbourElement2);

		// Both the attempted direction and current direction hit a wall, so stop moving and invalidate that direction
		if (isElementWallOrInvalid(prevValidDirectionNeighbourElement1)
				|| isElementWallOrInvalid(prevValidDirectionNeighbourElement2)) {
			velocityComponent.stopMovement();
			directionInputComponent.setNoDirection();
		} else {
			// Keep moving in the last known valid direction. The character will keep moving in
			// this direction until a wall is hit or the attempted current direction from
			// directionInputComponent becomes valid
			velocityComponent.setVelocityFromDirection(lastKnownValidDirection);
		}
	} else {
		// Current direction was valid; update the last known valid to be that
		lastValidDirectionComponent.setLastKnownValidDirection(direction);
	}
}

bool WallPathingSystem::isElementWallOrInvalid(int element) {
	return element == MapLayoutElements::WALL
		|| element == MapLayoutElements::INVALID;
}

void WallPathingSystem::getNeighbourElementsByDirection(Directions::Direction direction, Rect rect, int& neighbourElement1, int& neighbourElement2) const {
	switch (direction) {
		case Directions::UP: {
			Point bottomLeft = rect.bottomLeft();
			Point bottomRight = rect.bottomRight();
			// Don't overlap with where the next tile starts, on the right/bottom
			bottomLeft.setY(bottomLeft.y() - 1);
			bottomRight.setX(bottomRight.x() - 1);
			bottomRight.setY(bottomRight.y() - 1);

			neighbourElement1 = mMap.neighbourElement(bottomLeft, true, direction);
			neighbourElement2 = mMap.neighbourElement(bottomRight, true, direction);
			break;
		}
		case Directions::RIGHT: {
			Point topLeft = rect.topLeft();
			Point bottomLeft = rect.bottomLeft();
			// Don't overlap with where the next tile starts, on the right/bottom
			bottomLeft.setY(bottomLeft.y() - 1);

			neighbourElement1 = mMap.neighbourElement(topLeft, true, direction);
			neighbourElement2 = mMap.neighbourElement(bottomLeft, true, direction);
			break;
		}
		case Directions::DOWN: {
			Point topRight = rect.topRight();
			Point topLeft = rect.topLeft();
			// Don't overlap with where the next tile starts, on the right/bottom
			topRight.setX(topRight.x() - 1);

			neighbourElement1 = mMap.neighbourElement(topRight, true, direction);
			neighbourElement2 = mMap.neighbourElement(topLeft, true, direction);
			break;
		}
		case Directions::LEFT: {
			Point topRight = rect.topRight();
			Point bottomRight = rect.bottomRight();
			// Don't overlap with where the next tile starts, on the right/bottom
			topRight.setX(topRight.x() - 1);
			bottomRight.setX(bottomRight.x() - 1);
			bottomRight.setY(bottomRight.y() - 1);

			neighbourElement1 = mMap.neighbourElement(topRight, true, direction);
			neighbourElement2 = mMap.neighbourElement(bottomRight, true, direction);
			break;
		}
		default: {
			neighbourElement1 = MapLayoutElements::INVALID;
			neighbourElement2 = MapLayoutElements::INVALID;
		}
	}
}
