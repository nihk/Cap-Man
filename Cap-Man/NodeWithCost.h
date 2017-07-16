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
	// TODO: This should probably be in a constructor overload
	void setCost(const NodeWithCost& goal);

	bool operator<(const NodeWithCost& other) const;
	bool operator==(const NodeWithCost& other) const;

	struct Hash {
		size_t operator() (const NodeWithCost& node) const {
			return Point::hash(node.point());
		}
	};

private:
	static const int AXIS_ALIGNED_MOVEMENT_COST;

	Point mPoint;
	std::shared_ptr<NodeWithCost> mParent;
	// The sum of the G and H costs
	int mF;
	// The cumulative movement cost from the parent to this node
	int mG;
	// The manhattan distance from this node to a goal node
	int mH;
};

