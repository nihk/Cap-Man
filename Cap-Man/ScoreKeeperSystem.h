#pragma once
#include "System.h"
#include <unordered_map>

class Map;

// TODO: How to handle eating the ghosts while on a powerup?
// TODO: Or maybe just have this sytem as a dedicated pellet eating system
class ScoreKeeperSystem 
	: public System {
public:
	ScoreKeeperSystem(Manager& manager, Map& map, std::unordered_map<int, int>& pellets);
	~ScoreKeeperSystem();

	void updateEntity(float delta, int entity) override;

private:
	Map& mMap;
	std::unordered_map<int, int>& mPellets;
};

