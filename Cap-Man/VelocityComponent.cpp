#include "VelocityComponent.h"

VelocityComponent::VelocityComponent(float vx, float vy, float speed)
	: VelocityComponent(Velocity(vx, vy), speed) {
}

VelocityComponent::VelocityComponent(Velocity velocity, float speed)
	: mVelocity(velocity)
	, mSpeed(speed) {
}

VelocityComponent::~VelocityComponent() {
}

void VelocityComponent::setVelocityFromDirection(Directions::Direction direction) {
	float vx = 0.0f;
	float vy = 0.0f;

	switch (direction) {
		case Directions::UP:		vy -= mSpeed;	break;
		case Directions::DOWN:		vy += mSpeed;	break;
		case Directions::LEFT:		vx -= mSpeed;	break;
		case Directions::RIGHT:		vx += mSpeed;	break;
		default:					/* nothing */	break;
	}

	setVelocity(vx, vy);
}
