#include "AStarComponent.h"
#include "Map.h"
#include "NodeWithCost.h"

#include <unordered_set>

AStarComponent::AStarComponent(Map& map) 
    : mMap(map) {
}

AStarComponent::AStarComponent(const AStarComponent& other) 
    : AStarComponent(other.mMap) {
}

AStarComponent::~AStarComponent() {
}

AStarComponent& AStarComponent::operator=(const AStarComponent& other) {
    this->mMap = other.mMap;
    return *this;
}

void AStarComponent::findPath(Point start, Point end) {
    NodeWithCost current(start, nullptr);
    NodeWithCost goal(end, nullptr);

    // The set of nodes to be considered
    std::unordered_set<NodeWithCost, NodeWithCost::Hash> open;
    // The set of nodes already looked at
    std::unordered_set<NodeWithCost, NodeWithCost::Hash> closed;

    open.insert(current);

    while (!open.empty()) {
        current = findLowestFCost(open);

        if (current == goal) {
            break;
        }

        open.erase(current);
        closed.insert(current);

        addValidNeighbourNodesToOpen(current, goal, open, closed);
    }

    extractOptimalPath(std::make_shared<NodeWithCost>(current));
}

void AStarComponent::popNextPathStep() {
    mOptimalPath.pop_front();
}

// O(n)
NodeWithCost AStarComponent::findLowestFCost(const std::unordered_set<NodeWithCost, NodeWithCost::Hash>& open) {
    auto it = open.begin();
    NodeWithCost lowest = *it;

    while (++it != open.end()) {
        NodeWithCost node = *it;
        if (node < lowest) {
            lowest = node;
        }
    }

    return lowest;
}

void AStarComponent::addValidNeighbourNodesToOpen(NodeWithCost& current, const NodeWithCost& goal, 
        std::unordered_set<NodeWithCost, NodeWithCost::Hash>& open, const std::unordered_set<NodeWithCost, NodeWithCost::Hash>& closed) const {
    int x = current.x();
    int y = current.y();

    Point north = Point(x, y - 1);
    Point east = Point(x + 1, y);
    Point south = Point(x, y + 1);
    Point west = Point(x - 1, y);

    tryAddNodeToOpen(north, current, goal, open, closed);
    tryAddNodeToOpen(east, current, goal, open, closed);
    tryAddNodeToOpen(south, current, goal, open, closed);
    tryAddNodeToOpen(west, current, goal, open, closed);
}

void AStarComponent::tryAddNodeToOpen(const Point& point, NodeWithCost& parent, const NodeWithCost& goal, 
        std::unordered_set<NodeWithCost, NodeWithCost::Hash>& open, const std::unordered_set<NodeWithCost, NodeWithCost::Hash>& closed) const {
    if (isValidMapCoord(point) && !isWall(point)) {
        NodeWithCost node = NodeWithCost(point, std::make_shared<NodeWithCost>(parent));
        bool isInOpen = open.find(node) != open.end();
        bool isInClosed = closed.find(node) != closed.end();
        if (!isInOpen && !isInClosed) {
            node.setCost(goal);
            open.insert(node);
        }
    }
}

bool AStarComponent::isValidMapCoord(const Point& point) const {
    return point.x() >= 0 && point.x() < mMap.columns()
        && point.y() >= 0 && point.y() < mMap.rows();
}

bool AStarComponent::isWall(const Point& point) const {
    return mMap.mapElement(point.x(), point.y()) == MapLayoutElements::WALL;
}

void AStarComponent::extractOptimalPath(std::shared_ptr<NodeWithCost> node) {
    while (node != nullptr) {
        mOptimalPath.emplace_front(node->point());
        node = node->parent();
    }
}
