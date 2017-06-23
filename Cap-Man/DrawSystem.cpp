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

void DrawSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	GraphicsComponent& graphicsComponent = mManager.getComponent<GraphicsComponent>(entity);

	graphicsComponent.draw(mRenderer, physicsComponent.rectangle());
}
