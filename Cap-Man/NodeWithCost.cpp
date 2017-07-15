#include "NodeWithCost.h"

const int NodeWithCost::AXIS_ALIGNED_MOVEMENT_COST = 1;

NodeWithCost::NodeWithCost(Point point, std::shared_ptr<NodeWithCost> parent) 
	: mPoint(point)
	, mParent(parent)
	, mF(0)
	, mG(0)
	, mH(0) {
}

NodeWithCost::~NodeWithCost() {
}

void NodeWithCost::setCost(const NodeWithCost& goal) {
	// Manhattan distance
	mH = abs(x() - goal.x()) + abs(y() - goal.y());
	int parentG = mParent != nullptr ? mParent->mG : 0;
	mG = parentG + AXIS_ALIGNED_MOVEMENT_COST;
	mF = mH + mG;
}

bool NodeWithCost::operator<(const NodeWithCost& other) const {
	return mF < other.mF;
}

bool NodeWithCost::operator==(const NodeWithCost& other) const {
	return mPoint == other.mPoint;
}
