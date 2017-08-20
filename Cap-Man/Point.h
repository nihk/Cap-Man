#pragma once
#include <SDL.h>
#include "Wrapper.h"

// TODO: Wrap floats, too?
class Point 
    : public Wrapper<SDL_Point> {
public:
    Point();
    Point(int x, int y);
    ~Point();

    bool                operator==(const Point& other) const;
    bool                operator!=(const Point& other) const;
    static size_t       hash(const Point& point);

    int                 x() const               { return mSdlPoint.x; }
    int                 y() const               { return mSdlPoint.y; }
    void                setX(int x)             { mSdlPoint.x = x; }
    void                setY(int y)             { mSdlPoint.y = y; }

                        // Assumes two points in units for all these bool checks
    bool                isAdjacentToOrOn(const Point& other) const;
    bool                isAdjacentAbove(const Point& other) const;
    bool                isAdjacentBelow(const Point& other) const;
    bool                isAdjacentLeft(const Point& other) const;
    bool                isAdjacentRight(const Point& other) const;

    double              distance(const Point& other) const;
    const SDL_Point*    data() const override   { return &mSdlPoint; }
    SDL_Point*          mutableData() override  { return &mSdlPoint; }

    struct Hash {
        size_t operator() (const Point& point) const {
            return hash(point);
        }
    };

private:
    SDL_Point   mSdlPoint;
};

