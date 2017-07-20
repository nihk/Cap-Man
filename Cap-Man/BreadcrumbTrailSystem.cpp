#include "BreadcrumbTrailSystem.h"
#include "BreadcrumbTrailComponent.h"
#include "PhysicsComponent.h"
#include "Manager.h"
#include "Map.h"

BreadcrumbTrailSystem::BreadcrumbTrailSystem(Manager& manager, Map& map) 
		: System(manager)
		, mMap(map) {
	insertRequiredComponent(PhysicsComponent::ID);
	insertRequiredComponent(BreadcrumbTrailComponent::ID);
}

BreadcrumbTrailSystem::~BreadcrumbTrailSystem() {
}

void BreadcrumbTrailSystem::updateEntity(float delta, int entity) {
	PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
	BreadcrumbTrailComponent& trailComponent = mManager.getComponent<BreadcrumbTrailComponent>(entity);

	Rect rect = physicsComponent.rect();
	Point center = rect.center();
	mMap.scalePixelsToUnits(center);

	trailComponent.addBreadcrumb(center);
}
