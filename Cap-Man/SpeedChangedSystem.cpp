#include "SpeedChangedSystem.h"
#include "PhysicsComponent.h"
#include "SpeedChangeWatcherComponent.h"
#include "Manager.h"
#include "Map.h"

SpeedChangedSystem::SpeedChangedSystem(Manager& manager, Map& map)
        : System(manager)
        , mMap(map) {
    insertRequiredComponent(PhysicsComponent::ID);
    insertRequiredComponent(SpeedChangeWatcherComponent::ID);
}

SpeedChangedSystem::~SpeedChangedSystem() {
}

void SpeedChangedSystem::updateEntity(float delta, int entity) {
    PhysicsComponent& physicsComponent = mManager.getComponent<PhysicsComponent>(entity);
    SpeedChangeWatcherComponent& speedWatcherComponent = mManager.getComponent<SpeedChangeWatcherComponent>(entity);

    if (speedWatcherComponent.speedChanged()) {
        Rect rect = physicsComponent.rect();
        int step = mMap.singleUnitPixels() / 4;
        Point topLeft = rect.topLeft();

        // Somewhat of a hack to normalize the physics position since I didn't properly
        // test multiple speeds and different frame rates. Ugh!
        topLeft.setX(topLeft.x() / step * step);
        topLeft.setY(topLeft.y() / step * step);
        rect.setTop(topLeft.y());
        rect.setLeft(topLeft.x());
        physicsComponent.setRect(rect);
        speedWatcherComponent.setSpeedChanged(false);
    }
}
