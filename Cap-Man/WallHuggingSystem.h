#pragma once

#include "System.h"
#include "DirectionInputComponent.h"
#include "Rect.h"
#include "LastValidDirectionComponent.h"
#include "VelocityComponent.h"

class Map;

class WallHuggingSystem 
	: public System {
public:
	WallHuggingSystem(Manager& manager, Map& map);
	~WallHuggingSystem();

	void updateEntity(float delta, int entity) override;

private:
	bool tryMovingInDirection(Directions::Direction direction, const Rect& rect) const;
	bool tryMovingInDirection(Directions::Direction direction, DirectionInputComponent& directionComponent, LastValidDirectionComponent& lastValidDirectionComponent, VelocityComponent& velocityComponent, const Rect& rect) const;
	static bool isElementWallOrInvalid(int element);
	void getNeighbourElementsByDirection(Directions::Direction direction, const Rect& rect, int& neighbourElement1, int& neighbourElement2) const;
	bool tryMovingPseudoRandomlyIfPresent(int entity, ::DirectionInputComponent& directionComponent, ::LastValidDirectionComponent& lastValidDirectionComponent, VelocityComponent& velocityComponent, const Rect& rect) const;

	Map& mMap;
};

