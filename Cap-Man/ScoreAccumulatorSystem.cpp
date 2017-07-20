#include "ScoreAccumulatorSystem.h"
#include "ScoreWatcherComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "Manager.h"
#include "PointsCollectorComponent.h"

ScoreAccumulatorSystem::ScoreAccumulatorSystem(Manager& manager) 
		: System(manager) {
	insertRequiredComponent(ScoreWatcherComponent::ID);
	insertRequiredComponent(GraphicsComponent::ID);
}

ScoreAccumulatorSystem::~ScoreAccumulatorSystem() {
}

void ScoreAccumulatorSystem::updateEntity(float delta, int entity) {
	ScoreWatcherComponent& scoreWatcherComponent = mManager.getComponent<ScoreWatcherComponent>(entity);
	GraphicsComponent& graphicsComponent = mManager.getComponent<GraphicsComponent>(entity);

	int scoreEntity = scoreWatcherComponent.watchedEntity();
	auto& pointsCollectorStore = mManager.getComponentStore<PointsCollectorComponent>();

	if (pointsCollectorStore.hasComponent(scoreEntity)) {
		PointsCollectorComponent& pointsCollectorComponent = pointsCollectorStore.getComponent(scoreEntity);
		int points = pointsCollectorComponent.points();
		graphicsComponent.update(delta, points);
	}
}
