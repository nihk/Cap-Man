#pragma once
#include "Component.h"
#include "Point.h"
#include <list>

/**
* Let's an entity leave a trail of "breadcrumbs" that others can follow
*/
class BreadcrumbTrailComponent
	: public Component<BreadcrumbTrailComponent> {
public:
	BreadcrumbTrailComponent();
	~BreadcrumbTrailComponent();

	void addBreadcrumb(Point point);
	int breadcrumbScore(const Point& point) const;
	Point nextBreadcrumb(const Point& point) const;
	Point nextBreadcrumb(int score) const;
	int hasBreadcrumb(const Point& point) const;

private:
	static const int MAX_SCORE;
	static const int MIN_SCORE;
	static const int NO_SCORE;

	void removeBreadcrumb(const Point& point);

	// A list of breadcrumbs. The position from the head is the score.
	// The head is the lowest scoring breadcrumb, the last element is the highest scoring.
	// This list will be no bigger than size of the MAX_SCORE constant
	std::list<Point> mBreadcrumbs;
};

