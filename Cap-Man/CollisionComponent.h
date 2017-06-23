#pragma once

#include "Component.h"

class CollisionComponent 
	: public Component<CollisionComponent> {
public:
	// TODO: Need a name for the quality that it's doesn't let other entities clip through it
	CollisionComponent(bool isCollidable);
	~CollisionComponent();

	bool hasCollision() const { return mHasCollision; }
	void setHasCollision(bool hasCollision) { mHasCollision = hasCollision; }

	bool isCollidable() const { return mIsCollidable; }
	void setCollidable(bool isCollidable) { mIsCollidable = isCollidable; }

private:
	bool mHasCollision;
	bool mIsCollidable;
};

