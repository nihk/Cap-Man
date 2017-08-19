#include "TemporaryExistenceSystem.h"
#include "TemporaryExistenceComponent.h"
#include "PhysicsComponent.h"
#include "Manager.h"
#include "GraphicsComponent.h"

TemporaryExistenceSystem::TemporaryExistenceSystem(Manager& manager)
		: System(manager) {
	insertRequiredComponent(TemporaryExistenceComponent::ID);
	insertRequiredComponent(GraphicsComponent::ID);
}

TemporaryExistenceSystem::~TemporaryExistenceSystem() {
}

void TemporaryExistenceSystem::updateEntity(float delta, int entity) {
	TemporaryExistenceComponent& temporaryExistenceComponent = mManager.getComponent<TemporaryExistenceComponent>(entity);
	GraphicsComponent& graphicsComponent = mManager.getComponent<GraphicsComponent>(entity);

	temporaryExistenceComponent.update(delta);

	if (!temporaryExistenceComponent.exists() && !temporaryExistenceComponent.wasRemoved()) {
		graphicsComponent.setShouldDraw(false);
		temporaryExistenceComponent.setWasRemoved(true);
	}
}
