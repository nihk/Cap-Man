#include "PelletMonitoringSystem.h"
#include "PhysicsComponent.h"
#include "Manager.h"
#include "PointsCollectorComponent.h"
#include "Map.h"
#include "GraphicsComponent.h"
#include "WinConditionComponent.h"
#include "Game.h"

const int PelletMonitoringSystem::PELLET_POINT_VALUE = 10;

PelletMonitoringSystem::PelletMonitoringSystem(Manager& manager, Map& map, 
	std::unordered_map<int, int>& pellets, std::unordered_set<int>& consumedEntities,
	int& gameState)
		: System(manager)
		, mMap(map)
		, mPellets(pellets)
		, mConsumedEntities(consumedEntities)
		, mGameState(gameState) {
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
		int pelletEntity = mPellets.at(mapLayoutIndex);
		auto& physicsComponentStore = mManager.getComponentStore<PhysicsComponent>();
		auto& graphicsComponentStore = mManager.getComponentStore<GraphicsComponent>();
		
		bool isConsumedPellet = mConsumedEntities.find(pelletEntity) != mConsumedEntities.end();
		
		if (physicsComponentStore.hasComponent(pelletEntity) 
				&& graphicsComponentStore.hasComponent(pelletEntity)
				&& !isConsumedPellet) {
			mManager.unregisterEntity(pelletEntity);
			mConsumedEntities.insert(pelletEntity);
			pointsComponent.addPoints(PELLET_POINT_VALUE);

			int totalPelletsEaten = pointsComponent.points() / PELLET_POINT_VALUE;
			int pelletsEatenThisGame = totalPelletsEaten - winConditionComponent.numGamesWon() * mPellets.size();
			bool hasWon = pelletsEatenThisGame == mPellets.size();

			// Collected all the pellets. Game is therefore won.
			if (hasWon) {
				winConditionComponent.setWon();
				mGameState = Game::STATE_RESET_ALL;
			}
		}
	}
}
