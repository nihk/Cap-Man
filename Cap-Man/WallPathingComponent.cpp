#include "WallPathingComponent.h"
#include "Map.h"

WallPathingComponent::WallPathingComponent(Map& map)
	: mLastKnownValidDirection(Directions::NONE)
	, mMap(map){
}

WallPathingComponent::WallPathingComponent(const WallPathingComponent& other) 
	: WallPathingComponent(other.mMap) {
}

WallPathingComponent::~WallPathingComponent() {
}

WallPathingComponent& WallPathingComponent::operator=(const WallPathingComponent& other) {
	this->mMap = other.mMap;
	return *this;
}
