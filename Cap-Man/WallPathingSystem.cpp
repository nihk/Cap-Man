#include "WallPathingSystem.h"
#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "WallPathingComponent.h"
#include "CollisionComponent.h"
#include "Manager.h"

WallPathingSystem::WallPathingSystem(Manager& manager)
		: System(manager) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(VelocityComponent::ID);
	insertRequiredComponent(WallPathingComponent::ID);
	//insertRequiredComponent(CollisionComponent::ID);
}

WallPathingSystem::~WallPathingSystem() {
}

void WallPathingSystem::updateEntity(float delta, int entity) {
	// TODO
	// Get location on 
	VelocityComponent& velocityComponent = mManager.getComponent<VelocityComponent>(entity);
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	WallPathingComponent& wallPathingComponent = mManager.getComponent<WallPathingComponent>(entity);
}
