#include "CollisionSystem.h"
#include "CollidableComponent.h"
#include "PhysicsComponent.h"
#include "Manager.h"
#include "Map.h"
#include "TeleportComponent.h"

CollisionSystem::CollisionSystem(Manager& manager, Map& map)
		: System(manager)
		, mMap(map) {
	insertRequiredComponent(CollidableComponent::ID);
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(TeleportComponent::ID);
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	TeleportComponent& teleportComponent = mManager.getComponent<TeleportComponent>(entity);
	Rect rect = physicsComponent.rect();
	Point center = rect.center();

	int buffer = 1;
	Point topLeft = rect.topLeft();
	Point topRight = rect.topRight();
	Point bottomLeft = rect.bottomLeft();
	Point bottomRight = rect.bottomRight();

	// Handle overlapping points
	topRight.setX(topRight.x() - buffer);
	bottomLeft.setY(bottomLeft.y() - buffer);
	bottomRight.setY(bottomRight.y() - buffer);
	bottomRight.setX(bottomRight.x() - buffer);

	// Teleports are designed to let the entity go off the map
	if (teleportComponent.portPadA().containsRect(rect)
			|| teleportComponent.portPadB().containsRect(rect)) {
		return;
	}

	mMap.scalePixelsToUnits(center);
	mMap.scalePixelsToUnits(topLeft);
	mMap.scalePixelsToUnits(topRight);
	mMap.scalePixelsToUnits(bottomLeft);
	mMap.scalePixelsToUnits(bottomRight);

	// The right and bottom sides of any tile overlap with the left and top sides
	// of the adjacent tile. This value compensates for that when checking for collisions
	int tileOverlapCompensation = 1;

	if (mMap.mapElement(topLeft) == MapLayoutElements::WALL) {
		Point wallElement = topLeft;
		mMap.scaleUnitsToPixels(wallElement);
		Rect wallTile = Rect(wallElement.x(), wallElement.y(), mMap.singleUnitPixels(), mMap.singleUnitPixels());

		if (topLeft.x() < center.x()) {
			rect.setLeft(wallTile.right());
		} else if (topLeft.y() < center.y()) {
			rect.setTop(wallTile.bottom());
		}

	} else if (mMap.mapElement(topRight) == MapLayoutElements::WALL) {
		Point wallElement = topRight;
		mMap.scaleUnitsToPixels(wallElement);
		Rect wallTile = Rect(wallElement.x(), wallElement.y(), mMap.singleUnitPixels(), mMap.singleUnitPixels());

		if (center.x() < topRight.x()) {
			rect.setRight(wallTile.left() - tileOverlapCompensation);
		} else if (topRight.y() < center.y()) {
			rect.setTop(wallTile.bottom());
		}

	} else if (mMap.mapElement(bottomLeft) == MapLayoutElements::WALL) {
		Point wallElement = bottomLeft;
		mMap.scaleUnitsToPixels(wallElement);
		Rect wallTile = Rect(wallElement.x(), wallElement.y(), mMap.singleUnitPixels(), mMap.singleUnitPixels());

		if (bottomLeft.x() < center.x()) {
			rect.setLeft(wallTile.right());
		} else if (center.y() < bottomLeft.y()) {
			rect.setBottom(wallTile.top() - tileOverlapCompensation);
		}

	} else if (mMap.mapElement(bottomRight) == MapLayoutElements::WALL) {
		Point wallElement = bottomRight;
		mMap.scaleUnitsToPixels(wallElement);
		Rect wallTile = Rect(wallElement.x(), wallElement.y(), mMap.singleUnitPixels(), mMap.singleUnitPixels());
		rect.setLeft(wallTile.left());

		if (center.x() < bottomRight.x()) {
			rect.setRight(wallTile.left() - tileOverlapCompensation);
		} else if (center.y() < bottomRight.y()) {
			rect.setBottom(wallTile.top() - tileOverlapCompensation);
		}
	}

	physicsComponent.setRect(rect);
}
