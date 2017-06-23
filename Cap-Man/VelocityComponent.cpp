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
