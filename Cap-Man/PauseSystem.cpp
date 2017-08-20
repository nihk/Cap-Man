#include "PauseSystem.h"
#include "PauseComponent.h"
#include "Manager.h"
#include "BreadcrumbFollowerSystem.h"
#include "BreadcrumbTrailSystem.h"
#include "MoveSystem.h"
#include "PathfindingSystem.h"
#include "PelletMonitoringSystem.h"
#include "SpeedSystem.h"
#include "TeleportSystem.h"
#include "WallHuggingSystem.h"
#include "DirectionAnimationSystem.h"
#include "SystemControllerComponent.h"

const bool PauseSystem::PAUSE = false;
const bool PauseSystem::UNPAUSE = true;

PauseSystem::PauseSystem(Manager& manager) 
        : System(manager)
        , mAreSystemsPaused(false) {
    insertRequiredComponent(PauseComponent::ID);
    insertRequiredComponent(SystemControllerComponent::ID);
}

PauseSystem::~PauseSystem() {
}

void PauseSystem::updateEntity(float delta, int entity) {
    PauseComponent& pauseComponent = mManager.getComponent<PauseComponent>(entity);
    SystemControllerComponent& systemControllerComponent = mManager.getComponent<SystemControllerComponent>(entity);

    pauseComponent.update(delta);
    bool shouldPause = pauseComponent.shouldPause();
    const std::vector<std::string>& typeNames = systemControllerComponent.systemTypes();

    if (!mAreSystemsPaused && shouldPause) {
        togglePause(PAUSE, typeNames);
        setSystemsPaused(true);
    } else if (mAreSystemsPaused && !shouldPause) {
        togglePause(UNPAUSE, typeNames);
        setSystemsPaused(false);
    }
}

void PauseSystem::togglePause(bool shouldPause, const std::vector<std::string>& typeNames) const {
    for (const auto& typeName : typeNames) {
        mManager.toggleSystemUpdatability(typeName, shouldPause);
    }
}
