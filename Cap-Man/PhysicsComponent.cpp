#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(int x, int y, int w, int h) 
	: PhysicsComponent(Rectangle(x, y, w, h)) {
}

PhysicsComponent::PhysicsComponent(Rectangle rectangle) 
	: mRectangle(rectangle) {
}

PhysicsComponent::~PhysicsComponent() {
}

void PhysicsComponent::moveBy(int dx, int dy) {
	mRectangle.setLeft(mRectangle.left() + dx);
	mRectangle.setTop(mRectangle.top() + dy);
}
