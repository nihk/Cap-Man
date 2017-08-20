#pragma once
#include "Component.h"
#include "Constants.h"
#include "Rect.h"

// Two way teleport capability from specific locations
class TeleportComponent 
    : public Component<TeleportComponent> {
public:
    TeleportComponent(Rect portPadA, Directions::Direction emergantSideA, Rect portPadB, Directions::Direction emergantSideB);
    ~TeleportComponent();

    Rect portPadA() const { return mPortPadA; }
    Rect portPadB() const { return mPortPadB; }
    Directions::Direction emergantSideA() const { return mEmergantSideA; }
    Directions::Direction emergantSideB() const { return mEmergantSideB; }

private:
    // The rects of the two way teleport pads, scaled to pixels
    Rect mPortPadA;
    Rect mPortPadB;
    Directions::Direction mEmergantSideA;
    Directions::Direction mEmergantSideB;
};

