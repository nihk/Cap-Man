#include "PathGoalComponent.h"

PathGoalComponent::PathGoalComponent() 
	: PathGoalComponent(Point(-1, -1)) {
}

PathGoalComponent::PathGoalComponent(const Point& initialGoal)
	: mGoal(initialGoal) {
}

PathGoalComponent::~PathGoalComponent() {
}
