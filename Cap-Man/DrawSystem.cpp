#include "DrawSystem.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "Manager.h"

DrawSystem::DrawSystem(Manager& manager, Renderer& renderer) 
		: System(manager)
		, mRenderer(renderer) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(GraphicsComponent::ID);
}

DrawSystem::~DrawSystem() {
}

size_t DrawSystem::updateEntities(float delta) {
	mRenderer.clear();
	size_t numUpdatedEntities = System::updateEntities(delta);
	mRenderer.present();

	return numUpdatedEntities;
}

void DrawSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	GraphicsComponent& graphicsComponent = mManager.getComponent<GraphicsComponent>(entity);

	if (graphicsComponent.shouldDraw()) {
		graphicsComponent.draw(mRenderer, physicsComponent.rect());
	}
}
