#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(bool isRigidBody)
	: mHasCollision(false)
	, mIsCollidable(isRigidBody) {
}

CollisionComponent::~CollisionComponent() {
}
