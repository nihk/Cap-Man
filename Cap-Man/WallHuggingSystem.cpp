#include "WallHuggingSystem.h"
#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "LastValidDirectionComponent.h"
#include "Manager.h"
#include "Map.h"

WallHuggingSystem::WallHuggingSystem(Manager& manager, Map& map)
		: System(manager)
		, mMap(map) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(VelocityComponent::ID);
	insertRequiredComponent(LastValidDirectionComponent::ID);
	insertRequiredComponent(DirectionInputComponent::ID);
}

WallHuggingSystem::~WallHuggingSystem() {
}

void WallHuggingSystem::updateEntity(float delta, int entity) {
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

bool WallHuggingSystem::isElementWallOrInvalid(int element) {
	return element == MapLayoutElements::WALL
		|| element == MapLayoutElements::INVALID;
}

/**
 * An entity is represented by an AABB. Despite this game being tile-based, the entity's physics component
 * can overlap either 1, 2, or 4 tiles at any given time. The "feet" of the AABB will overlap either 1 or 2
 * map tile elements, e.g. when an entity is moving upward, its bottom left and bottom right points will
 * touch either 1 or 2 tiles. The neighbourElement1 and neighbourElement2 params here represent what element
 * is in those tiles that the entity's physicscomponent's "feet" are touching.
 */
void WallHuggingSystem::getNeighbourElementsByDirection(Directions::Direction direction, Rect rect, int& neighbourElement1, int& neighbourElement2) const {
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
