#include "WallPathingSystem.h"
#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "DirectionValidatorComponent.h"
#include "CollisionComponent.h"
#include "Manager.h"
#include "Map.h"

WallPathingSystem::WallPathingSystem(Manager& manager, Map& map)
		: System(manager)
		, mMap(map) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(VelocityComponent::ID);
	insertRequiredComponent(DirectionValidatorComponent::ID);
	insertRequiredComponent(DirectionInputComponent::ID);
}

WallPathingSystem::~WallPathingSystem() {
}

void WallPathingSystem::updateEntity(float delta, int entity) {
	DirectionInputComponent& directionInputComponent = mManager.getComponent<DirectionInputComponent>(entity);
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	DirectionValidatorComponent& directionValidatorComponent = mManager.getComponent<DirectionValidatorComponent>(entity);
	VelocityComponent& velocityComponent = mManager.getComponent<VelocityComponent>(entity);

	if (!velocityComponent.isMoving()) {
		return;
	}

	int direction = directionInputComponent.direction();
	Rect rect = physicsComponent.rect();

	int neighbourElement1;
	int neighbourElement2;

	getNeighbourElementsByDirection(direction, rect, neighbourElement1, neighbourElement2);

	// TODO: Wrap this into a method
	if (neighbourElement1 == MapLayoutElements::WALL
			|| neighbourElement1 == MapLayoutElements::INVALID
			|| neighbourElement2 == MapLayoutElements::WALL
			|| neighbourElement2 == MapLayoutElements::INVALID) {
		Directions::Direction lastKnownValidDirection = directionValidatorComponent.lastKnownValidDirection();

		int prevValidDirectionNeighbourElement1;
		int prevValidDirectionNeighbourElement2;

		getNeighbourElementsByDirection(lastKnownValidDirection, rect, prevValidDirectionNeighbourElement1, prevValidDirectionNeighbourElement2);

		// TODO: Wrap this into a method
		if (prevValidDirectionNeighbourElement1 == MapLayoutElements::WALL 
				|| prevValidDirectionNeighbourElement1 == MapLayoutElements::INVALID
				|| prevValidDirectionNeighbourElement2 == MapLayoutElements::WALL
				|| prevValidDirectionNeighbourElement2 == MapLayoutElements::INVALID) {
			// TODO: Move to method: VelocityComponent.stopMovement();
			velocityComponent.setVelocity(0.0f, 0.0f);
			// TODO: Clean this up or rethink its logic
			//directionInputComponent.cancelInput();
			//directionValidatorComponent.setLastKnownValidDirection(Directions::NONE);
		} else {
			// FIXME: Move this logic to velocityComponent itself!
			float speed = velocityComponent.speed();

			float vx = 0.0f;
			float vy = 0.0f;

			switch (lastKnownValidDirection) {
				case Directions::UP:		vy -= speed;	break;
				case Directions::DOWN:		vy += speed;	break;
				case Directions::LEFT:		vx -= speed;	break;
				case Directions::RIGHT:		vx += speed;	break;
				default:									break;
			}

			velocityComponent.setVelocity(vx, vy);
		}
	} else {
		directionValidatorComponent.setLastKnownValidDirection(direction);
	}
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

			neighbourElement1 = mMap.getNeighbourElement(bottomLeft, true, direction);
			neighbourElement2 = mMap.getNeighbourElement(bottomRight, true, direction);
			break;
		}
		case Directions::RIGHT: {
			Point topLeft = rect.topLeft();
			Point bottomLeft = rect.bottomLeft();
			// Don't overlap with where the next tile starts, on the right/bottom
			bottomLeft.setY(bottomLeft.y() - 1);

			neighbourElement1 = mMap.getNeighbourElement(topLeft, true, direction);
			neighbourElement2 = mMap.getNeighbourElement(bottomLeft, true, direction);
			break;
		}
		case Directions::DOWN: {
			Point topRight = rect.topRight();
			Point topLeft = rect.topLeft();
			// Don't overlap with where the next tile starts, on the right/bottom
			topRight.setX(topRight.x() - 1);

			neighbourElement1 = mMap.getNeighbourElement(topRight, true, direction);
			neighbourElement2 = mMap.getNeighbourElement(topLeft, true, direction);
			break;
		}
		case Directions::LEFT: {
			Point topRight = rect.topRight();
			Point bottomRight = rect.bottomRight();
			// Don't overlap with where the next tile starts, on the right/bottom
			topRight.setX(topRight.x() - 1);
			bottomRight.setX(bottomRight.x() - 1);
			bottomRight.setY(bottomRight.y() - 1);

			neighbourElement1 = mMap.getNeighbourElement(topRight, true, direction);
			neighbourElement2 = mMap.getNeighbourElement(bottomRight, true, direction);
			break;
		}
		default: {
			neighbourElement1 = MapLayoutElements::INVALID;
			neighbourElement2 = MapLayoutElements::INVALID;
		}
	}
}
