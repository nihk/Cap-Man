#pragma once
#include "Component.h"

class PointGranterComponent 
	: public Component<PointGranterComponent> {
public:
	PointGranterComponent(int pointsToGrant);
	~PointGranterComponent();

	int pointsToGrant() const { return mPointsToGrant; }

private:
	int mPointsToGrant;
};

