#include "CapManAttackedSystem.h"
#include "PhysicsComponent.h"
#include "Manager.h"
#include "LifeCollisionComponent.h"
#include "Game.h"
#include "ResetComponent.h"
#include "VulnerabilityComponent.h"
#include "DeathComponent.h"

CapManAttackedSystem::CapManAttackedSystem(Manager& manager, int& state, std::vector<int>& lifeEntities, std::unordered_set<int>& consumedEntities)
		: System(manager)
		, mGameState(state) 
		, mLifeEntities(lifeEntities)
		, mConsumedEntities(consumedEntities) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(LifeCollisionComponent::ID);
	insertRequiredComponent(ResetComponent::ID);
}

CapManAttackedSystem::~CapManAttackedSystem() {
}

// TODO: Need to not pause capman's death animation but pause the ghosts'
// TODO: Extract into smaller methods
void CapManAttackedSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	LifeCollisionComponent& lifeCollisionComponent = mManager.getComponent<LifeCollisionComponent>(entity);
	ResetComponent& resetComponent = mManager.getComponent<ResetComponent>(entity);

	LifeCollisionComponent::Type type = lifeCollisionComponent.type();

	// Only care about life holders
	if (type == LifeCollisionComponent::Type::TAKER) {
		return;
	}

	auto& lifeStore = mManager.getComponentStore<LifeCollisionComponent>();
	auto& physicsStore = mManager.getComponentStore<PhysicsComponent>();
	auto& vulnerabilityStore = mManager.getComponentStore<VulnerabilityComponent>();
	auto& deathStore = mManager.getComponentStore<DeathComponent>();

	Rect lifeHolderRect = physicsComponent.rect();

	// Check all other life takers and see if there's a collision
	for (auto& pair : lifeStore.getStore()) {
		int storeEntity = pair.first;

		// No point in comparing the entity against himself
		if (entity == storeEntity
			|| lifeStore.getComponent(storeEntity).type() == LifeCollisionComponent::Type::HOLDER
			// This should always be false, i.e. I defined all entities with velocities to also have physics
			|| !physicsStore.hasComponent(storeEntity)) {
			continue;
		}

		auto& vulnerabilityComponent = vulnerabilityStore.getComponent(storeEntity);
		auto& deathComponent = deathStore.getComponent(storeEntity);
		if (vulnerabilityComponent.isVulnerable() || deathComponent.isDead()) {
			// Capman is invulnerable when high on a powerup
			return;
		}

		auto& storePhysicsComponent = physicsStore.getComponent(storeEntity);
		Rect rect = storePhysicsComponent.rect();
		Point center = rect.center();
		if (lifeHolderRect.containsPoint(center)) {
			// Remove lives and set the game state based on how many are remaining
			auto rit = mLifeEntities.rbegin();
			bool hasLivesRemaining = false;
			while (rit != mLifeEntities.rend()) {
				int lifeEntity = *rit;
				bool isConsumedLife = mConsumedEntities.find(lifeEntity) != mConsumedEntities.end();
				if (!isConsumedLife) {
					mConsumedEntities.insert(lifeEntity);
					mManager.unregisterEntity(lifeEntity);
					hasLivesRemaining = true;
					mGameState = Game::STATE_RESET_CHARACTERS;
					break;
				}
				++rit;
			}
			if (!hasLivesRemaining) {
				mGameState = Game::STATE_RESET_ALL;
			}
		}
	}
}
