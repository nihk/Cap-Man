#pragma once

#include "System.h"
#include "Constants.h"
#include "Point.h"

class Rect;

class TeleportSystem 
	: public System {
public:
	TeleportSystem(Manager& manager);
	~TeleportSystem();

	void updateEntity(float delta, int entity) override;

private:
	static void emerge(::Rect& rect /* out */, const Point& center, const Rect& emergantPortPad, Directions::Direction emergingSide);
};

