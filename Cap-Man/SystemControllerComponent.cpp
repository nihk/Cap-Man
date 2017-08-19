#include "SystemControllerComponent.h"
#include "BreadcrumbFollowerSystem.h"
#include "BreadcrumbTrailSystem.h"
#include "MoveSystem.h"
#include "PathfindingSystem.h"
#include "PelletMonitoringSystem.h"
#include "DirectionAnimationSystem.h"
#include "SpeedSystem.h"
#include "TeleportSystem.h"
#include "WallHuggingSystem.h"
#include "PseudoRandomDirectionSystem.h"
#include "ResetSystem.h"

SystemControllerComponent::SystemControllerComponent() {
	mSystemTypes = {
		typeid(BreadcrumbFollowerSystem).name(),
		typeid(BreadcrumbTrailSystem).name(),
		typeid(MoveSystem).name(),
		typeid(PathfindingSystem).name(),
		typeid(PelletMonitoringSystem).name(),
		typeid(DirectionAnimationSystem).name(),
		typeid(SpeedSystem).name(),
		typeid(TeleportSystem).name(),
		typeid(WallHuggingSystem).name(),
		typeid(PseudoRandomDirectionSystem).name(),
		typeid(ResetSystem).name(),
	};
}

SystemControllerComponent::~SystemControllerComponent() {
}
