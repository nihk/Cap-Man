#include "VelocityComponent.h"

VelocityComponent::VelocityComponent(float vx, float vy, float speed)
	: VelocityComponent(Velocity(vx, vy), speed) {
}

VelocityComponent::VelocityComponent(Velocity velocity, float speed)
	: mVelocity(velocity)
	, mSpeed(speed)
	, mCurrentSpeed(speed)
	, mHalfSpeed(speed * 0.5f)
	, mDoubleSpeed(speed * 2.0f) {
}

VelocityComponent::~VelocityComponent() {
}

void VelocityComponent::setVelocityFromDirection(Directions::Direction direction) {
	float vx = 0.0f;
	float vy = 0.0f;

	switch (direction) {
		case Directions::UP:		vy -= mCurrentSpeed;	break;
		case Directions::DOWN:		vy += mCurrentSpeed;	break;
		case Directions::LEFT:		vx -= mCurrentSpeed;	break;
		case Directions::RIGHT:		vx += mCurrentSpeed;	break;
		default:					/* do nothing */		break;
	}

	setVelocity(vx, vy);
}
