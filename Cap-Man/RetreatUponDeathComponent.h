#pragma once
#include "Component.h"
#include "Point.h"

class RetreatUponDeathComponent 
	: public Component<RetreatUponDeathComponent> {
public:
	RetreatUponDeathComponent(Point home);
	~RetreatUponDeathComponent();

	bool isHome(Point& point) const { return point == mHome; }
	const Point& home() const { return mHome; }

private: 
	Point mHome;  // in units, not pixels
};

