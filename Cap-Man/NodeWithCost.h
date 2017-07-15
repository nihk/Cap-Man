#pragma once
#include "Point.h"
#include <memory>

class NodeWithCost {
public:
	NodeWithCost(Point point, std::shared_ptr<NodeWithCost> parent);
	~NodeWithCost();

	Point point() const { return mPoint; }
	int x() const { return mPoint.x(); }
	int y() const { return mPoint.y(); }
	std::shared_ptr<NodeWithCost> parent() const { return mParent; }
	void setCost(const NodeWithCost& goal);

	bool operator<(const NodeWithCost& other) const;
	bool operator==(const NodeWithCost& other) const;

private:
	static const int AXIS_ALIGNED_MOVEMENT_COST;

	Point mPoint;
	std::shared_ptr<NodeWithCost> mParent;
	int mF;
	int mG;
	int mH;
};

