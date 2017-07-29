#include "PelletMonitoringSystem.h"
#include "PhysicsComponent.h"
#include "Manager.h"
#include "PointsCollectorComponent.h"
#include "Map.h"
#include "GraphicsComponent.h"
#include "WinConditionComponent.h"

PelletMonitoringSystem::PelletMonitoringSystem(Manager& manager, Map& map, std::unordered_map<int, int>& pellets, std::unordered_set<int>& consumedEntities)
		: System(manager)
		, mMap(map)
		, mPellets(pellets)
		, mConsumedEntities(consumedEntities) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(PointsCollectorComponent::ID);
	insertRequiredComponent(WinConditionComponent::ID);
}

PelletMonitoringSystem::~PelletMonitoringSystem() {
}

void PelletMonitoringSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	PointsCollectorComponent& pointsComponent = mManager.getComponent<PointsCollectorComponent>(entity);
	WinConditionComponent& winConditionComponent = mManager.getComponent<WinConditionComponent>(entity);

	Rect rect = physicsComponent.rect();
	Point center = rect.center();
	mMap.scalePixelsToUnits(center);
	int element = mMap.mapElement(center.x(), center.y());

	if (element == MapLayoutElements::PELLET) {
		int mapLayoutIndex = mMap.mapLocation(center, false);
		bool isActivePellet = mPellets.find(mapLayoutIndex) != mPellets.end();
		if (!isActivePellet) {
			return;
		}
		int pelletEntity = mPellets.at(mapLayoutIndex);
		auto& physicsComponentStore = mManager.getComponentStore<PhysicsComponent>();
		auto& graphicsComponentStore = mManager.getComponentStore<GraphicsComponent>();
		
		bool isConsumedPellet = mConsumedEntities.find(pelletEntity) != mConsumedEntities.end();
		
		if (physicsComponentStore.hasComponent(pelletEntity) 
				&& graphicsComponentStore.hasComponent(pelletEntity)
				&& !isConsumedPellet) {
			mManager.unregisterEntity(pelletEntity);
			mConsumedEntities.insert(pelletEntity);
			// TODO: Magic number
			pointsComponent.addPoints(10);

			// Collected all the pellets. Game is therefore won.
			if (mPellets.empty()) {
				winConditionComponent.setWon(true);
			}
		}
	}
}
