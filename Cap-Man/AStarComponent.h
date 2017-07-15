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
	Point popNextPathStep();
	Point peekCurrentPathStep() const { return mOptimalPath.front(); }

private:
	struct NodePointHash {
		size_t operator() (const NodeWithCost& node) const {
			int result = node.x();
			result = 31 * result + node.y();
			return result;
		}
	};

	static NodeWithCost findLowestFCost(const std::unordered_set<NodeWithCost, NodePointHash>& open);
	void addValidNeighbourNodesToOpen(NodeWithCost& current, const NodeWithCost& goal,
	                                  std::unordered_set<NodeWithCost, NodePointHash>& open, const std::unordered_set<NodeWithCost, NodePointHash>& closed) const;
	void tryAddNodeToOpen(const Point& point, NodeWithCost& parent,
	                      const NodeWithCost& goal, std::unordered_set<NodeWithCost, NodePointHash>& open, const std::unordered_set<NodeWithCost, NodePointHash>& closed) const;
	bool isValidMapCoord(const Point& point) const;
	bool isWall(const Point& point) const;
	void extractOptimalPath(std::shared_ptr<NodeWithCost> node);

	Map& mMap;
	std::deque<Point> mOptimalPath;
};

