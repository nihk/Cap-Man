#pragma once
#include "Component.h"

class PointsCollectorComponent 
	: public Component<PointsCollectorComponent> {
public:
	PointsCollectorComponent();
	PointsCollectorComponent(int initialPoints);
	~PointsCollectorComponent();

	int points() const { return mPoints; }
	void setPoints(int points) { mPoints = points; }
	void addPoints(int points) { mPoints += points; }
	void resetPoints() { mPoints = 0; }

private:
	int mPoints;
};

