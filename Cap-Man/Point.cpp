#include "Point.h"

Point::Point() 
	: Point(0, 0) {
}

Point::Point(int x, int y) 
	: mSdlPoint(SDL_Point{ x, y }) {
}

Point::~Point() {
}

double Point::distance(const Point& other) const {
	int xDistance = abs(x() - other.x());
	int yDistance = abs(y() - other.y());
	return sqrt(xDistance * xDistance + yDistance * yDistance);
}
