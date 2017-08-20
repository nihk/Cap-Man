#pragma once
#include "Rect.h"

Rect::Rect() 
    : Rect(0,0,0,0) {
}

Rect::Rect(int x, int y, int w, int h) 
    : mSdlRect(SDL_Rect{ x,y,w,h }) {
}

Rect::Rect(const Rect& other) 
    : mSdlRect(other.mSdlRect) {
}

Rect& Rect::operator=(const Rect& other) {
    mSdlRect = other.mSdlRect;
    return *this;
}

bool Rect::operator==(const Rect& other) const {
    return mSdlRect.x == other.mSdlRect.x
        && mSdlRect.y == other.mSdlRect.y
        && mSdlRect.h == other.mSdlRect.h
        && mSdlRect.w == other.mSdlRect.w;
}

Point Rect::center() const {
    return Point(left() + width() / 2, top() + height() / 2);
}

Point Rect::topLeft() const {
    return Point(left(), top());
}

Point Rect::topRight() const {
    return Point(right(), top());
}

Point Rect::bottomRight() const {
    return Point(right(), bottom());
}

Point Rect::bottomLeft() const {
    return Point(left(), bottom());
}

float Rect::area() const {
    return static_cast<float>(mSdlRect.w * mSdlRect.h);
}

void Rect::setCenter(int x, int y) {
    setCenter(Point(x, y));
}

void Rect::setCenter(const Point& point) {
    setLeft(point.x() - width() / 2);
    setTop(point.y() - height() / 2);
}

bool Rect::isWithinScreenBounds(int sw, int sh) const {
        return left() > 0
            && right() < sw
            && top() > 0
            && bottom() < sh;
}

bool Rect::containsPoint(const Point& point) const {
    return SDL_PointInRect(point.data(), &mSdlRect) == SDL_TRUE;
}

bool Rect::containsRect(const Rect& rect) const {
    return SDL_HasIntersection(&mSdlRect, &rect.mSdlRect) == SDL_TRUE;
}