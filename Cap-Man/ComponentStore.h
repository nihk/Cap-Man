#pragma once
#include <unordered_map>
#include "Component.h"

class IComponentStore {
public:
	virtual ~IComponentStore() = default;
};

template<class T, class = std::enable_if<std::is_base_of<Component<T>, T>::value>>
class ComponentStore
	: public IComponentStore {
public:
	ComponentStore() : mComponentId(T::ID) {}
	~ComponentStore() {}

	bool							addComponent(int entity, T&& component)		{ return mStore.insert_or_assign(entity, component).second; }
	bool							removeComponent(int entity)					{ return mStore.erase(entity) > 0; }
	bool							hasComponent(int entity) const				{ return mStore.end() != mStore.find(entity); }
	T&								getComponent(int entity)					{ return mStore.at(entity); }
	std::unordered_map<int, T>&		getStore()									{ return mStore; }

	T extractComponent(int entity) {
		T component = std::move(mStore.at(entity));
		removeComponent(entity);
		return component;
	}

private:
	// A map of entity IDs to their respective component of class T
	std::unordered_map<int, T>		mStore;
	const int						mComponentId;
};