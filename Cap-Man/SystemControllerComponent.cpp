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
#include "VulnerableAnimationSystem.h"
#include "CapManAttackedSystem.h"
#include "GhostEatenSystem.h"
#include "PowerupMonitoringSystem.h"
#include "SpeedChangedSystem.h"

SystemControllerComponent::SystemControllerComponent() {
    mSystemTypes = {
        typeid(BreadcrumbFollowerSystem).name(),
        typeid(BreadcrumbTrailSystem).name(),
        typeid(MoveSystem).name(),
        typeid(PathfindingSystem).name(),
        typeid(PelletMonitoringSystem).name(),
        typeid(PowerupMonitoringSystem).name(),
        typeid(DirectionAnimationSystem).name(),
        typeid(VulnerableAnimationSystem).name(),
        typeid(SpeedSystem).name(),
        typeid(TeleportSystem).name(),
        typeid(WallHuggingSystem).name(),
        typeid(PseudoRandomDirectionSystem).name(),
        typeid(ResetSystem).name(),
        typeid(CapManAttackedSystem).name(),
        typeid(GhostEatenSystem).name(),
        typeid(SpeedChangedSystem).name(),
    };
}

SystemControllerComponent::~SystemControllerComponent() {
}
