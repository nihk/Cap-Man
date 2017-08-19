#include "ResetSystem.h"
#include "PhysicsComponent.h"
#include "ResetComponent.h"
#include "AStarComponent.h"
#include "PathGoalComponent.h"
#include "PointsCollectorComponent.h"
#include "WinConditionComponent.h"
#include "VulnerabilityComponent.h"
#include "VelocityComponent.h"
#include "DeathComponent.h"

ResetSystem::ResetSystem(Manager& manager, int& state, std::unordered_set<int>& consumedEntities)
		: System(manager)
		, mGameState(state)
		, mConsumedEntities(consumedEntities) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(ResetComponent::ID);
}

ResetSystem::~ResetSystem() {
}

// TODO: Rethink this. It knows too much about other non-required components
size_t ResetSystem::updateEntities(float delta) {
	size_t numUpdatedEntities = 0;

	if (mGameState != Game::STATE_NORMAL) {
		if (mGameState & Game::STATE_RESET_ALL) {
			// Re-register entities that were potentially consumed
			auto it = mConsumedEntities.begin();
			while (it != mConsumedEntities.end()) {
				int entity = *it;
				mManager.registerEntity(entity);
				it = mConsumedEntities.erase(it);
			}

			bool hasWon = false;
			auto& winConditionStore = mManager.getComponentStore<WinConditionComponent>();
			for (auto& pair : winConditionStore.getStore()) {
				auto& winComponent = pair.second;
				if (winComponent.hasWon()) {
					hasWon = true;
					winComponent.nextRound();
				} else {
					winComponent.reset();
				}
			}

			// Only reset the score if the player lost, otherwise keep accumulating them
			if (!hasWon) {
				auto& pointsStore = mManager.getComponentStore<PointsCollectorComponent>();
				for (auto& pair : pointsStore.getStore()) {
					auto& pointsComponent = pair.second;
					pointsComponent.resetPoints();
				}
			}
		}

		auto& physicsStore = mManager.getComponentStore<PhysicsComponent>();
		auto& resetStore = mManager.getComponentStore<ResetComponent>();
		auto& directionStore = mManager.getComponentStore<DirectionInputComponent>();
		auto& aStarStore = mManager.getComponentStore<AStarComponent>();
		auto& pathGoalStore = mManager.getComponentStore<PathGoalComponent>();
		auto& vulnStore = mManager.getComponentStore<VulnerabilityComponent>();
		auto& velocityStore = mManager.getComponentStore<VelocityComponent>();
		auto& deathStore = mManager.getComponentStore<DeathComponent>();
		for (auto& pair : resetStore.getStore()) {
			int entity = pair.first;
			auto& physicsComponent = physicsStore.getComponent(entity);
			auto& resetComponent = pair.second;

			if (resetComponent.resettableStates() & mGameState) {
				Rect rect = physicsComponent.rect();
				Point resetPoint = resetComponent.startPosition();
				rect.setLeft(resetPoint.x());
				rect.setTop(resetPoint.y());
				physicsComponent.setRect(rect);

				if (directionStore.hasComponent(entity)) {
					auto& directionComponent = directionStore.getComponent(entity);
					directionComponent.setDirection(resetComponent.startDirection());
				}
				if (aStarStore.hasComponent(entity)) {
					auto& aStarComponent = aStarStore.getComponent(entity);
					aStarComponent.purgePath();
				}
				if (pathGoalStore.hasComponent(entity)) {
					auto& pathGoalComponent = pathGoalStore.getComponent(entity);
					pathGoalComponent.removeGoal();
				}
				if (vulnStore.hasComponent(entity)) {
					auto& vulnComponent = vulnStore.getComponent(entity);
					vulnComponent.reset();
				}
				if (velocityStore.hasComponent(entity)) {
					auto& velComponent = velocityStore.getComponent(entity);
					velComponent.setCurrentSpeed(velComponent.defaultSpeed());
				}
				if (deathStore.hasComponent(entity)) {
					auto& deathComponent = deathStore.getComponent(entity);
					deathComponent.setDead(false);
				}

				++numUpdatedEntities;
			}
		}

		// Reset the game state now that its been handled
		mGameState = Game::STATE_NORMAL;
	}

	return numUpdatedEntities;
}

void ResetSystem::updateEntity(float delta, int entity) {
	// Do nothing. All the updating is done in one fell swoop of ResetSystem::updateEntities()
}
