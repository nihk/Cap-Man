#pragma once
#include "Component.h"
#include "NodeWithCost.h"
#include <deque>
#include <unordered_set>

class Point;
class Map;

class AStarComponent 
	: public Component<AStarComponent> {
public:
	AStarComponent(Map& map);
	AStarComponent(const AStarComponent& other);
	~AStarComponent();

	AStarComponent& operator=(const AStarComponent& other);

	void findPath(Point start, Point end);
	bool hasPath() const { return !mOptimalPath.empty(); }
	void popNextPathStep();
	Point peekCurrentPathStep() const { return mOptimalPath.front(); }

private:
	static NodeWithCost findLowestFCost(const std::unordered_set<NodeWithCost, NodeWithCost::Hash>& open);
	void addValidNeighbourNodesToOpen(NodeWithCost& current, const NodeWithCost& goal,
	                                  std::unordered_set<NodeWithCost, NodeWithCost::Hash>& open, const std::unordered_set<NodeWithCost, NodeWithCost::Hash>& closed) const;
	void tryAddNodeToOpen(const Point& point, NodeWithCost& parent,
	                      const NodeWithCost& goal, std::unordered_set<NodeWithCost, NodeWithCost::Hash>& open, const std::unordered_set<NodeWithCost, NodeWithCost::Hash>& closed) const;
	bool isValidMapCoord(const Point& point) const;
	bool isWall(const Point& point) const;
	void extractOptimalPath(std::shared_ptr<NodeWithCost> node);

	Map& mMap;
	std::deque<Point> mOptimalPath;
};

