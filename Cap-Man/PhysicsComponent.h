#pragma once
#include "Component.h"
#include "Rect.h"

class PhysicsComponent 
    : public Component<PhysicsComponent> {
public:
    PhysicsComponent(int x, int y, int w, int h);
    PhysicsComponent(Rect rect);
    ~PhysicsComponent();

    Rect rect() const { return mRect; }
    void setRect(Rect rect) { mRect = rect; }
    void moveBy(int dx, int dy);

private:
    Rect mRect;
};

