#include "RetreatComponent.h"
#include <iostream>

const int RetreatComponent::TRAVERSE_START_VALUE = 3;
const int RetreatComponent::END_VALUE = 2;

RetreatComponent::RetreatComponent(Map& map)
		: mMap(map) {
	initOrResetTraversalMap();
}

RetreatComponent::RetreatComponent(const RetreatComponent& other)
	: mMap(other.mMap)
	, mTraversalMap(other.mTraversalMap)
	, mTraverseValue(other.mTraverseValue) {
}

RetreatComponent::~RetreatComponent() {
}

RetreatComponent& RetreatComponent::operator=(const RetreatComponent& other) {
	this->mMap = other.mMap;
	this->mTraversalMap = other.mTraversalMap;
	this->mTraverseValue = other.mTraverseValue;
	return *this;
}

void RetreatComponent::initOrResetTraversalMap() {
	mTraverseValue = TRAVERSE_START_VALUE;
	mReachedEnd = false;

	for (int i = 0; i < mMap.rows(); ++i) {
		std::vector<int> row;
		for (int j = 0; j < mMap.columns(); ++j) {
			int element = mMap.mapElement(j, i);

			if (element == MapLayoutElements::WALL) {
				row.push_back(element);
			} else {
				row.push_back(MapLayoutElements::EMPTY_NAVIGABLE_SPACE);
			}
		}
		mTraversalMap.push_back(row);
	}
}

void RetreatComponent::calculateRetreatPath(Point start, Point end) {
	//mTraversalMap[end.y()][end.x()] = END_VALUE;

	//traverseMap(start.y(), start.x());

	//for (std::vector<int> vec : mTraversalMap) {
	//	for (int i : vec) {
	//		std::cout << "" << i << "  ";
	//	}
	//	std::cout << std::endl;
	//}
}

// TODO: This pathfinding algorithm is TERRIBLE. It's costly and doesn't end with an optimal path. Find a better one: e.g. Dijkstra's
// http://bryukh.com/labyrinth-algorithms/
// http://www.cokeandcode.com/main/tutorials/path-finding/
bool RetreatComponent::traverseMap(int currRow, int currCol) {
	// Array bounds checking
	if (currRow < 0 || currCol < 0 || currRow >= mMap.rows() || currCol >= mMap.columns()) return false;

	int node = mTraversalMap[currRow][currCol];
	// Wall or already traversed cell checking
	if (node == MapLayoutElements::WALL || node >= TRAVERSE_START_VALUE) return false;

	// Else: cell was untraversed, so mark it so
	mTraversalMap[currRow][currCol] = mTraverseValue++;

	// End of maze reached
	if (node == END_VALUE) return true;

	// If end of maze reached, don't continue (keep returning true)
	if (traverseMap(currRow + 1, currCol)) return true;
	if (traverseMap(currRow - 1, currCol)) return true;
	if (traverseMap(currRow, currCol + 1)) return true;
	if (traverseMap(currRow, currCol - 1)) return true;

	// Didn't find the right way or the end, so clear the x
	mTraversalMap[currRow][currCol] = MapLayoutElements::EMPTY_NAVIGABLE_SPACE;

	return false;
}
