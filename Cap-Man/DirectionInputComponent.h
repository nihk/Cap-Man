#pragma once
#include "Component.h"
#include "Constants.h"

class DirectionInputComponent
    : public Component<DirectionInputComponent> {
public:
    DirectionInputComponent();
    DirectionInputComponent(Directions::Direction startingDirection);
    ~DirectionInputComponent();

    virtual Directions::Direction direction() { return mDirection; }
    virtual void setDirection(Directions::Direction direction) { mDirection = direction; }
    virtual void setNoDirection() { setDirection(Directions::NONE); }

protected:
    Directions::Direction mDirection;
};

