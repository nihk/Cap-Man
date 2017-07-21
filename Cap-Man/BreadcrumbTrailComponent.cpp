#include "BreadcrumbTrailComponent.h"

const int BreadcrumbTrailComponent::MAX_SCORE = 10;
const int BreadcrumbTrailComponent::MIN_SCORE = 1;
const int BreadcrumbTrailComponent::NO_SCORE = 0;

BreadcrumbTrailComponent::BreadcrumbTrailComponent() {
}

BreadcrumbTrailComponent::~BreadcrumbTrailComponent() {
}

void BreadcrumbTrailComponent::addBreadcrumb(Point point) {
	// No current breadcrumbs or already sitting on the highest scoring breadcrumb, 
	// so return
	if (!mBreadcrumbs.empty() && mBreadcrumbs.back() == point) {
		return;
	}

	// Otherwise if the trailblazer revisited an old point, e.g. walking in a circle 
	// under 15 points in length. So remove it, enabling it to be inserted again as 
	// the highest scoring Point
	if (hasBreadcrumb(point)) {
		removeBreadcrumb(point);
	}

	mBreadcrumbs.emplace_back(point);

	if (mBreadcrumbs.size() == MAX_SCORE) {
		mBreadcrumbs.pop_front();
	}
}

int BreadcrumbTrailComponent::breadcrumbScore(const Point& point) const {
	int score = MIN_SCORE;

	if (!mBreadcrumbs.empty()) {
		for (const auto& p : mBreadcrumbs) {
			if (point == p) {
				return score;
			}
			++score;
		}
	}

	return NO_SCORE;
}

Point BreadcrumbTrailComponent::nextBreadcrumb(const Point& point) const {
	if (!hasBreadcrumb(point)) {
		return point;
	}

	auto it = mBreadcrumbs.begin();

	while (it != mBreadcrumbs.end() && *it != point) {
		// Increment the iterator to the current Point position
		++it;
	}

	// If the next element past the given point param was the end, 
	// there's nowhere else to go but where you are
	if (it == mBreadcrumbs.end()) {
		return point;
	}

	// Increment to the next Point position based on score;
	++it;

	// One last check...
	if (it == mBreadcrumbs.end()) {
		return point;
	}

	return *it;
}

Point BreadcrumbTrailComponent::nextBreadcrumb(int score) const {
	if (score == MAX_SCORE) {
		// Can't get a higher score than the last element
		return mBreadcrumbs.back();
	}

	int counter = 0;
	auto it = mBreadcrumbs.begin();

	while (counter != score) {
		// Increment the iterator to the current Point position
		++it;
		++counter;
	}
	
	// Increment to the next Point position based on score;
	++it;

	return *it;
}

int BreadcrumbTrailComponent::hasBreadcrumb(const Point& point) const {
	return breadcrumbScore(point) > NO_SCORE;
}

void BreadcrumbTrailComponent::removeBreadcrumb(const Point& point) {
	auto it = mBreadcrumbs.begin();

	while (it != mBreadcrumbs.end()) {
		if (*it == point) {
			mBreadcrumbs.erase(it);
			break;
		}
		++it;
	}
}
