#pragma once
#include "Component.h"
#include "Rectangle.h"

class PhysicsComponent 
	: public Component<PhysicsComponent> {
public:
	PhysicsComponent(int x, int y, int w, int h);
	PhysicsComponent(Rectangle rectangle);
	~PhysicsComponent();

	Rectangle rectangle() const { return mRectangle; }
	void setRectangle(Rectangle rectangle) { mRectangle = rectangle; }
	void moveBy(int dx, int dy);

private:
	Rectangle mRectangle;
};

