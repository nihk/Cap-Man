#pragma once
#include "Component.h"
#include "Point.h"

class PathGoalComponent 
	: public Component<PathGoalComponent> {
public:
	PathGoalComponent();
	PathGoalComponent(Point initialGoal);
	~PathGoalComponent();

	Point goal() const { return mGoal; }
	bool hasGoal() const { return mGoal.x() >= 0 && mGoal.y() >= 0; }
	void removeGoal() { mGoal.setX(-1); mGoal.setY(-1); }
	void setGoal(Point goal) { mGoal = goal; }

private:
	Point mGoal;
};

