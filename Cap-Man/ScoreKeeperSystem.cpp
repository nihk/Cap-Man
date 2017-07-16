#include "ScoreKeeperSystem.h"
#include "PhysicsComponent.h"
#include "Manager.h"
#include "PointsCollectorComponent.h"
#include "Map.h"
#include "GraphicsComponent.h"

ScoreKeeperSystem::ScoreKeeperSystem(Manager& manager, Map& map, std::unordered_map<int, int>& pellets)
		: System(manager)
		, mMap(map)
		, mPellets(pellets) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(PointsCollectorComponent::ID);
}

ScoreKeeperSystem::~ScoreKeeperSystem() {
}

void ScoreKeeperSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	PointsCollectorComponent& pointsComponent = mManager.getComponent<PointsCollectorComponent>(entity);

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
		
		if (physicsComponentStore.hasComponent(pelletEntity) && graphicsComponentStore.hasComponent(pelletEntity)) {
			graphicsComponentStore.removeComponent(pelletEntity);
			graphicsComponentStore.removeComponent(pelletEntity);
			mManager.unregisterEntity(pelletEntity);
			mPellets.erase(mapLayoutIndex);
			// TODO: Magic number
			pointsComponent.addPoints(10);
		}
	}
}
