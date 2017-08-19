#pragma once
#include "System.h"
#include <unordered_map>
#include <unordered_set>

class Map;

class PelletMonitoringSystem 
	: public System {
public:
	PelletMonitoringSystem(Manager& manager, Map& map, std::unordered_map<int, int>& pellets, std::unordered_set<int>& consumedEntities, int& gameState);
	~PelletMonitoringSystem();

	void updateEntity(float delta, int entity) override;

private:
	Map& mMap;
	std::unordered_map<int, int>& mPellets;
	std::unordered_set<int>& mConsumedEntities;
	int& mGameState;
};

