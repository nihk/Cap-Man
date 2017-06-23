#pragma once
#include <unordered_map>
#include <set>
#include <memory>
#include "ComponentStore.h"
#include "System.h"
#include "Component.h"

class Manager {
public:
	Manager();
	~Manager();

	// Creates a map of component IDs to component stores (which are themselves maps of 
	// entity IDs to components)
	template<class T, class = std::enable_if<std::is_base_of<Component<T>, T>::value>>
	bool createComponentStore() {
		return mComponentStores.insert_or_assign(T::ID, std::make_unique<ComponentStore<T>>()).second;
	}

	template<class T, class = std::enable_if<std::is_base_of<Component<T>, T>::value>>
	ComponentStore<T>& getComponentStore() {
		std::unordered_map<int, std::unique_ptr<IComponentStore>>::iterator componentStoreIt = mComponentStores.find(T::ID);
		if (mComponentStores.end() == componentStoreIt) {
			throw std::runtime_error("The ComponentStore does not exist");
		}

		return reinterpret_cast<ComponentStore<T>&>(*(componentStoreIt->second));
	}

	template<class T, class = std::enable_if<std::is_base_of<Component<T>, T>::value>>
	T& getComponent(int entity) {
		ComponentStore<T>& componentStore = getComponentStore<T>();
		if (componentStore.hasComponent(entity)) {
			return componentStore.getComponent(entity);
		} else {
			throw std::runtime_error("Entity does not exist within that ComponentStore");
		}
	}

	template<class T, class = std::enable_if<std::is_base_of<Component<T>, T>::value>>
	bool addComponent(int entity, T&& component) {
		// If the entity was newly created, this set will be empty
		auto& entityComponents = findEntityComponents(entity);
		entityComponents.insert(T::ID);

		// Add the Component to the corresponding Store
		ComponentStore<T>& componentStore = getComponentStore<T>();
		return componentStore.addComponent(entity, std::move(component));
	}

	void			addSystem(const std::shared_ptr<System>& system);
	int				createEntity();
	size_t			registerEntity(int entity);
	size_t			unregisterEntity(int entity);
	size_t			updateSystems(float delta);

private:
	std::set<int>&	findEntityComponents(int entity);

	// A map of an entity ID to its set of component IDs
	std::unordered_map<int, std::set<int>>							mEntityComponents;
	// A map of component IDs to their respective component store (a map of an entity to component). 
	// This is useful for getting all entities that use a particular component type
	std::unordered_map<int, std::unique_ptr<IComponentStore>>		mComponentStores;
	// The order they are inserted is the order they are updated, e.g. plan insertions accordingly
	// if you're depending on something like input->velocity->physics->draw
	std::vector<std::shared_ptr<System>>							mSystems;
};

