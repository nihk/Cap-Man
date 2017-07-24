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

const bool PauseSystem::PAUSE = false;
const bool PauseSystem::UNPAUSE = true;

PauseSystem::PauseSystem(Manager& manager) 
		: System(manager)
		, mAreSystemsPaused(false) {
	insertRequiredComponent(PauseComponent::ID);
}

PauseSystem::~PauseSystem() {
}

void PauseSystem::updateEntity(float delta, int entity) {
	PauseComponent& pauseComponent = mManager.getComponent<PauseComponent>(entity);
	pauseComponent.update(delta);

	bool shouldPause = pauseComponent.shouldPause();

	if (!mAreSystemsPaused && shouldPause) {
		togglePause(PAUSE);
		setSystemsPaused(true);
	} else if (mAreSystemsPaused && !shouldPause) {
		togglePause(UNPAUSE);
		setSystemsPaused(false);
	}
}

void PauseSystem::togglePause(bool shouldPause) const {
	mManager.toggleSystemUpdatability(typeid(BreadcrumbFollowerSystem), shouldPause);
	mManager.toggleSystemUpdatability(typeid(BreadcrumbTrailSystem), shouldPause);
	mManager.toggleSystemUpdatability(typeid(MoveSystem), shouldPause);
	mManager.toggleSystemUpdatability(typeid(PathfindingSystem), shouldPause);
	mManager.toggleSystemUpdatability(typeid(PelletMonitoringSystem), shouldPause);
	mManager.toggleSystemUpdatability(typeid(DirectionAnimationSystem), shouldPause);
	mManager.toggleSystemUpdatability(typeid(SpeedSystem), shouldPause);
	mManager.toggleSystemUpdatability(typeid(TeleportSystem), shouldPause);
	mManager.toggleSystemUpdatability(typeid(WallHuggingSystem), shouldPause);
}
