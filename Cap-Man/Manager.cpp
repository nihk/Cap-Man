#include "Manager.h"
#include <algorithm>

Manager::Manager() {
}

Manager::~Manager() {
}

void Manager::addSystem(std::type_index typeIndex, const std::shared_ptr<System>& system) {

	if (!system || system->getRequiredComponents().empty()) {
		throw std::runtime_error("System did not specify required Components");
	}

	mSystems.insert_or_assign(typeIndex, system);
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
	for (auto& pair : mSystems) {
		std::shared_ptr<System> system = pair.second;
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

	for (auto& pair : mSystems) {
		std::shared_ptr<System> system = pair.second;
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

	for (auto& pair : mSystems) {
		std::shared_ptr<System> system = pair.second;
		system->updateEntities(delta);
		++numUpdatedSystems;
	}

	return numUpdatedSystems;
}

void Manager::toggleSystemUpdatability(std::type_index typeIndex, bool shouldUpdate) {
	std::shared_ptr<System> system = mSystems.at(typeIndex);
	system->setUpdatable(shouldUpdate);
}

// Finds the set of components that a particular entity uses
std::set<int>& Manager::findEntityComponents(int entity) {
	auto entityComponentsIt = mEntityComponents.find(entity);
	if (mEntityComponents.end() == entityComponentsIt) {
		throw std::runtime_error("The Entity does not exist");
	}
	return entityComponentsIt->second;
}
