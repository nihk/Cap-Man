#pragma once
#include "Component.h"
#include "Point.h"
#include "Constants.h"

class ResetComponent 
    : public Component<ResetComponent> {
public:
    // Start position in pixels, not units
    ResetComponent(Point startPosition, int resettableStates);
    ResetComponent(Point startPosition, int resettableStates, Directions::Direction startDirection);
    ~ResetComponent();

    Point startPosition() const { return mStartPosition; }
    int resettableStates() const { return mResettableStates; }
    Directions::Direction startDirection() const { return mStartDirection; }

private:
    Point mStartPosition;
    int mResettableStates;
    Directions::Direction mStartDirection;
};

