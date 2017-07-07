#include "Manager.h"
#include <algorithm>

Manager::Manager() {
}

Manager::~Manager() {
}

void Manager::addSystem(const std::shared_ptr<System>& system) {
	if (!system || system->getRequiredComponents().empty()) {
		throw std::runtime_error("System did not specify required Components");
	}

	mSystems.push_back(system);
}

int Manager::createEntity() {
	int id = UID::generate();
	mEntityComponents.insert_or_assign(id, std::set<int>());
	return id;
}

// Register an entity to all matching systems.
size_t Manager::registerEntity(int entity) {
	size_t numAssociatedSystems = 0;

	std::set<int>& entityComponents = findEntityComponents(entity);

	// Cycle through all systems to check which ones can be registered by the entity
	for (auto& system : mSystems) {
		auto systemRequiredComponents = system->getRequiredComponents();

		// Check if all components required by the system are what the entity uses
		if (std::includes(entityComponents.begin(), entityComponents.end(),
			systemRequiredComponents.begin(), systemRequiredComponents.end())) {
			// Register the matching entity
			system->registerEntity(entity);
			++numAssociatedSystems;
		}
	}

	return numAssociatedSystems;
}

size_t Manager::unregisterEntity(int entity) {
	size_t numSystemsUnregisteredFrom = 0;

	for (auto& system : mSystems) {
		numSystemsUnregisteredFrom += system->unregisterEntity(entity);
	}

	return numSystemsUnregisteredFrom;
}

void Manager::clear() {
	mEntityComponents.clear();
	mComponentStores.clear();
	mSystems.clear();
}

size_t Manager::updateSystems(float delta) {
	size_t numUpdatedSystems = 0;

	for (auto& system : mSystems) {
		system->updateEntities(delta);
		++numUpdatedSystems;
	}

	return numUpdatedSystems;
}

// Finds the set of components that a particular entity uses
std::set<int>& Manager::findEntityComponents(int entity) {
	auto entityComponentsIt = mEntityComponents.find(entity);
	if (mEntityComponents.end() == entityComponentsIt) {
		throw std::runtime_error("The Entity does not exist");
	}
	return entityComponentsIt->second;
}
