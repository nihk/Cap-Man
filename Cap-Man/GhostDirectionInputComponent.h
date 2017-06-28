#pragma once

#include "DirectionInputComponent.h"
#include "Map.h"

// TODO: This class might actually not be necessary
class GhostDirectionInputComponent 
	: public DirectionInputComponent {
public:
	GhostDirectionInputComponent(Map& map);
	~GhostDirectionInputComponent();

	Directions::Direction direction() override;

private:
	Map& mMap;
};

