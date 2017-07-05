#include "GhostDeathRetreatSystem.h"
#include "RetreatComponent.h"
#include "PhysicsComponent.h"
#include "Manager.h"

GhostDeathRetreatSystem::GhostDeathRetreatSystem(Manager& manager) 
		: System(manager) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(RetreatComponent::ID);
}

GhostDeathRetreatSystem::~GhostDeathRetreatSystem() {
}

void GhostDeathRetreatSystem::updateEntity(float delta, int entity) {
	RetreatComponent& retreatComponent = mManager.getComponent<RetreatComponent>(entity);
	retreatComponent.calculateRetreatPath(Point{ 10, 20 }, Point{ 10, 10 });
}
