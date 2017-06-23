#include "MoveSystem.h"
#include "PhysicsComponent.h"
#include "VelocityComponent.h"
#include "Manager.h"

MoveSystem::MoveSystem(Manager& manager)
		: System(manager) {
	insertRequiredComponent(VelocityComponent::ID);
	insertRequiredComponent(PhysicsComponent::ID);
}

MoveSystem::~MoveSystem() {
}

void MoveSystem::updateEntity(float delta, int entity) {
	VelocityComponent& velocityComponent = mManager.getComponent<VelocityComponent>(entity);
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);

	Velocity velocity = velocityComponent.velocity();
	int dx = static_cast<int>(velocity.calcDeltaX(delta));
	int dy = static_cast<int>(velocity.calcDeltaY(delta));

	physicsComponent.moveBy(dx, dy);
}
