#pragma once
#include <set>

class Manager;

class System {
public:
	System(Manager& manager);
	virtual ~System() = default;

	const std::set<int>&		getRequiredComponents() const			{ return mRequiredComponents; }
	bool						registerEntity(int entity)				{ return mMatchingEntities.insert(entity).second; }
	size_t						unregisterEntity(int entity)			{ return mMatchingEntities.erase(entity); }
	bool						hasEntity(int entity) const			    { return mMatchingEntities.end() != mMatchingEntities.find(entity); }
	virtual size_t				updateEntities(float delta);
	virtual void				updateEntity(float delta, int entity) = 0;
	bool						isUpdatable() const						{ return mIsUpdatable; }
	void						setUpdatable(bool shouldUpdate)			{ mIsUpdatable = shouldUpdate; }

protected:
	void						insertRequiredComponent(int component)	{ mRequiredComponents.insert(component); }

	std::set<int>				mMatchingEntities;
	Manager&					mManager;

private:
	std::set<int>				mRequiredComponents;
	bool						mIsUpdatable;
};

