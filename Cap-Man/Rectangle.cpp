#pragma once
#include "Rectangle.h"

Rectangle::Rectangle() 
	: Rectangle(0,0,0,0) {
}

Rectangle::Rectangle(int x, int y, int w, int h) 
	: mSdlRect(SDL_Rect{ x,y,w,h }) {
}

Point Rectangle::center() const {
	return Point(left() + width() / 2, top() + height() / 2);
}

Point Rectangle::topLeft() const {
	return Point(left(), top());
}

Point Rectangle::topRight() const {
	return Point(right(), top());
}

Point Rectangle::bottomRight() const {
	return Point(right(), bottom());
}

Point Rectangle::bottomLeft() const {
	return Point(left(), bottom());
}

float Rectangle::area() const {
	return static_cast<float>(mSdlRect.w * mSdlRect.h);
}

void Rectangle::setCenter(int x, int y) {
	setCenter(Point(x, y));
}

void Rectangle::setCenter(const Point& point) {
	setLeft(point.x() - width() / 2);
	setTop(point.y() - height() / 2);
}

bool Rectangle::isWithinScreenBounds(int sw, int sh) const {
		return left() > 0
			&& right() < sw
			&& top() > 0
			&& bottom() < sh;
}

bool Rectangle::containsPoint(const Point& point) const {
	return SDL_PointInRect(point.data(), &mSdlRect) == SDL_TRUE;
}

bool Rectangle::containsRect(const Rectangle& rect) const {
	return SDL_HasIntersection(&mSdlRect, &rect.mSdlRect) == SDL_TRUE;
}