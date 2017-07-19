#include "Point.h"

Point::Point() 
	: Point(0, 0) {
}

Point::Point(int x, int y) 
	: mSdlPoint(SDL_Point{ x, y }) {
}

Point::~Point() {
}

bool Point::operator==(const Point& other) const {
	return x() == other.x() && y() == other.y();
}

bool Point::operator!=(const Point& other) const {
	return !(*this == other);
}

size_t Point::hash(const Point& point) {
	int result = point.x();
	result = 31 * result + point.y();
	return result;
}

double Point::distance(const Point& other) const {
	int xDistance = abs(x() - other.x());
	int yDistance = abs(y() - other.y());
	return sqrt(xDistance * xDistance + yDistance * yDistance);
}
