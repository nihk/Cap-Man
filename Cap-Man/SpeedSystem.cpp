#include "SpeedSystem.h"
#include "VelocityComponent.h"
#include "Manager.h"
#include "DirectionInputComponent.h"

SpeedSystem::SpeedSystem(Manager& manager)
		: System(manager) {
	insertRequiredComponent(DirectionInputComponent::ID);
	insertRequiredComponent(VelocityComponent::ID);
}

SpeedSystem::~SpeedSystem() {
}

void SpeedSystem::updateEntity(float delta, int entity) {
	DirectionInputComponent& inputComponent = mManager.getComponent<DirectionInputComponent>(entity);
	VelocityComponent& velocityComponent = mManager.getComponent<VelocityComponent>(entity);

	Directions::Direction direction = inputComponent.direction();
	float speed = velocityComponent.speed();

	float vx = 0.0f;
	float vy = 0.0f;

	switch (direction) {
		case Directions::UP:		vy -= speed;	break;
		case Directions::DOWN:		vy += speed;	break;
		case Directions::LEFT:		vx -= speed;	break;
		case Directions::RIGHT:		vx += speed;	break;
		default:									break;
	}

	velocityComponent.setVelocity(vx, vy);
}
