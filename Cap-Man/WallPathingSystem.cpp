#include "WallPathingSystem.h"
#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "WallPathingComponent.h"
#include "CollisionComponent.h"

WallPathingSystem::WallPathingSystem(Manager& manager)
		: System(manager) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(VelocityComponent::ID);
	insertRequiredComponent(WallPathingComponent::ID);
	insertRequiredComponent(CollisionComponent::ID);
}

WallPathingSystem::~WallPathingSystem() {
}

void WallPathingSystem::updateEntity(float delta, int entity) {
	// TODO
}
