#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(int x, int y, int w, int h) 
	: PhysicsComponent(Rect(x, y, w, h)) {
}

PhysicsComponent::PhysicsComponent(Rect rect) 
	: mRect(rect) {
}

PhysicsComponent::~PhysicsComponent() {
}

void PhysicsComponent::moveBy(int dx, int dy) {
	mRect.setLeft(mRect.left() + dx);
	mRect.setTop(mRect.top() + dy);
}
