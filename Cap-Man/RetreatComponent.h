#pragma once

#include "Map.h"

class RetreatComponent 
	: public Component<RetreatComponent> {
public:
	RetreatComponent(Map& map);
	RetreatComponent(const RetreatComponent& other);
	~RetreatComponent();

	RetreatComponent& operator=(const RetreatComponent& other);

	void calculateRetreatPath(Point start, Point end);
	bool reachedEnd() const { return mReachedEnd; }

private:
	void initOrResetTraversalMap();
	bool traverseMap(int currRow, int currCol);

	static const int TRAVERSE_START_VALUE;
	static const int END_VALUE;

	Map& mMap;
	std::vector<std::vector<int>> mTraversalMap;
	int mTraverseValue;
	bool mReachedEnd;
};

