#include "PowerupMonitoringSystem.h"
#include "PowerupCollectorComponent.h"
#include "PhysicsComponent.h"
#include "Manager.h"
#include "Constants.h"
#include "Map.h"
#include "GraphicsComponent.h"
#include "VulnerabilityComponent.h"
#include "VelocityComponent.h"

PowerupMonitoringSystem::PowerupMonitoringSystem(Manager& manager, Map& map, 
			std::unordered_map<int, int>& powerups, std::unordered_set<int>& consumedEntities, std::unordered_set<int>& ghosts)
		: System(manager)
		, mMap(map)
		, mPowerups(powerups)
		, mConsumedEntities(consumedEntities)
		, mGhosts(ghosts) {
	insertRequiredComponent(PowerupCollectorComponent::ID);
	insertRequiredComponent(PhysicsComponent::ID);
}

PowerupMonitoringSystem::~PowerupMonitoringSystem() {
}

void PowerupMonitoringSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	PowerupCollectorComponent& powerupCollectorComponent = mManager.getComponent<PowerupCollectorComponent>(entity);

	Rect rect = physicsComponent.rect();
	Point center = rect.center();
	mMap.scalePixelsToUnits(center);
	int element = mMap.mapElement(center.x(), center.y());

	// TODO: Extract to method
	for (auto ghost : mGhosts) {
		auto& vulnerabilityComponent = mManager.getComponent<VulnerabilityComponent>(ghost);
		auto& velocityComponent = mManager.getComponent<VelocityComponent>(ghost);
		float defaultSpeed = static_cast<float>(mMap.unitPixels(GameConstants::CHARACTER_UNITS_SPEED));
		if (!vulnerabilityComponent.isVulnerable() && velocityComponent.currentSpeed() != defaultSpeed) {
			velocityComponent.setCurrentSpeed(defaultSpeed);
		}
	}

	if (element == MapLayoutElements::POWERUP) {
		int mapLayoutIndex = mMap.mapLocation(center, false);
		int powerupEntity = mPowerups.at(mapLayoutIndex);
		auto& physicsComponentStore = mManager.getComponentStore<PhysicsComponent>();
		auto& graphicsComponentStore = mManager.getComponentStore<GraphicsComponent>();

		bool isConsumedPowerup = mConsumedEntities.find(powerupEntity) != mConsumedEntities.end();

		if (physicsComponentStore.hasComponent(powerupEntity)
				&& graphicsComponentStore.hasComponent(powerupEntity)
				&& !isConsumedPowerup) {
			mManager.unregisterEntity(powerupEntity);
			mConsumedEntities.insert(powerupEntity);
			turnGhostsVulnerable();
		}
	}
}

void PowerupMonitoringSystem::turnGhostsVulnerable() const {
	for (auto ghost : mGhosts) {
		auto& vulnerabilityComponent = mManager.getComponent<VulnerabilityComponent>(ghost);
		auto& velocityComponent = mManager.getComponent<VelocityComponent>(ghost);
		vulnerabilityComponent.makeTemporarilyVulnerable(GameConstants::GHOST_VULNERABILITY_DURATION);
		velocityComponent.setCurrentSpeed(velocityComponent.halfSpeed());
	}
}
