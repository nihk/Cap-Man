#include "PathGoalComponent.h"

PathGoalComponent::PathGoalComponent() 
	: PathGoalComponent(Point(-1, -1)) {
}

PathGoalComponent::PathGoalComponent(Point initialGoal)
	: mGoal(initialGoal) {
}

PathGoalComponent::~PathGoalComponent() {
}
