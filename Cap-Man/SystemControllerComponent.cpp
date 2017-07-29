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
		typeid(BreadcrumbFollowerSystem),
		typeid(BreadcrumbTrailSystem),
		typeid(MoveSystem),
		typeid(PathfindingSystem),
		typeid(PelletMonitoringSystem),
		typeid(DirectionAnimationSystem),
		typeid(SpeedSystem),
		typeid(TeleportSystem),
		typeid(WallHuggingSystem),
		typeid(PseudoRandomDirectionSystem),
		typeid(ResetSystem),
	};
}

SystemControllerComponent::~SystemControllerComponent() {
}
