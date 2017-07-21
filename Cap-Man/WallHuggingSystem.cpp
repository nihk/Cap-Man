#include "WallHuggingSystem.h"
#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "LastValidDirectionComponent.h"
#include "Manager.h"
#include "Map.h"
#include "PseudoRandomDirectionComponent.h"
#include "Utils.h"

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

	if (!tryMovingInDirection(direction, directionInputComponent, lastValidDirectionComponent, velocityComponent, rect)) {
		// Current direction will hit a wall, so keep going in the last known valid one instead
		Directions::Direction lastKnownValidDirection = lastValidDirectionComponent.lastKnownValidDirection();

		if (!tryMovingInDirection(lastKnownValidDirection, directionInputComponent, lastValidDirectionComponent, velocityComponent, rect)) {

			// Both the attempted direction and current direction hit a wall, so try moving pseudo-randomly if possible
			if (!tryMovingPseudoRandomlyIfPresent(entity, directionInputComponent, lastValidDirectionComponent, velocityComponent, rect)) {
				// Otherwise, invalidate the direction
				velocityComponent.stopMovement();
				directionInputComponent.setNoDirection();
			}
		}
	}
}

bool WallHuggingSystem::tryMovingInDirection(Directions::Direction direction, const Rect& rect) const {
	int neighbourElement1;
	int neighbourElement2;

	getNeighbourElementsByDirection(direction, rect, neighbourElement1, neighbourElement2);

	return !isElementWallOrInvalid(neighbourElement1) && !isElementWallOrInvalid(neighbourElement2);
}

bool WallHuggingSystem::tryMovingInDirection(Directions::Direction direction, DirectionInputComponent& directionComponent, LastValidDirectionComponent& lastValidDirectionComponent, VelocityComponent& velocityComponent, const Rect& rect) const {
	int neighbourElement1;
	int neighbourElement2;

	getNeighbourElementsByDirection(direction, rect, neighbourElement1, neighbourElement2);

	if (!isElementWallOrInvalid(neighbourElement1) && !isElementWallOrInvalid(neighbourElement2)) {
		// Note that the directionComponent isn't set here. This is so that
		// the real directional intention of the entity is always preserved.
		velocityComponent.setVelocityFromDirection(direction);
		// If the direction param here was from the directionComponent, that direction
		// is navigable, so update the last known valid direction. Otherwise if this
		// was LastValidDirectionComponent's direction, this will just set itself to
		// the same value, which is pointless but it makes this method more flexible.
		lastValidDirectionComponent.setLastKnownValidDirection(direction);
		return true;
	}

	return false;
}

bool WallHuggingSystem::isElementWallOrInvalid(int element) {
	return element == MapLayoutElements::WALL
		|| element == MapLayoutElements::INVALID;
}

/**
 * An entity is represented by an AABB. Despite this game being tile-based, the proposed location for the next
 * position of the entity's physics component can overlap either 1, 2, or 4 tiles at any given time. The "feet" 
 * of the AABB will overlap either 1 or 2 map tile elements, e.g. when an entity is moving upward, its bottom 
 * left and bottom right points will touch either 1 or 2 tiles. The neighbourElement1 and neighbourElement2 
 * params here represent what element is in those tiles that the entity's physicscomponent's "feet" are touching.
 */
void WallHuggingSystem::getNeighbourElementsByDirection(Directions::Direction direction, const Rect& rect, int& neighbourElement1, int& neighbourElement2) const {
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

bool WallHuggingSystem::tryMovingPseudoRandomlyIfPresent(int entity, DirectionInputComponent& directionComponent, 
	LastValidDirectionComponent& lastValidDirectionComponent, VelocityComponent& velocityComponent, const Rect& rect) const {
	bool hasRandomCapability;
	auto& pseudoRandomStore = mManager.getComponentStore<PseudoRandomDirectionComponent>();
	if ((hasRandomCapability = pseudoRandomStore.hasComponent(entity))) {
		Directions::Direction lastValidDirection = lastValidDirectionComponent.lastKnownValidDirection();
		Directions::Direction turnedBack = DirectionUtils::turnBack(lastValidDirection);

		// Optimally, turn left or right from the current direction
		const int numOptimalDirections = 2;
		Directions::Direction turnedLeftAndRight[numOptimalDirections] = 
			{ DirectionUtils::turnLeft(lastValidDirection), DirectionUtils::turnRight(lastValidDirection) };
		int nextIndex = rand() % numOptimalDirections;
		Directions::Direction first = turnedLeftAndRight[nextIndex];
		nextIndex = (nextIndex + 1) % numOptimalDirections;
		Directions::Direction second = turnedLeftAndRight[nextIndex];

		// The order of walking left or right will be random
		if (tryMovingInDirection(first, directionComponent, lastValidDirectionComponent, velocityComponent, rect)) {
			directionComponent.setDirection(first);
		} else if (tryMovingInDirection(second, directionComponent, lastValidDirectionComponent, velocityComponent, rect)) {
			directionComponent.setDirection(second);
		} else {
			// Nowhere else to go now but back
			tryMovingInDirection(turnedBack, directionComponent, lastValidDirectionComponent, velocityComponent, rect);
			directionComponent.setDirection(turnedBack);
		}
	}

	return hasRandomCapability;
}
