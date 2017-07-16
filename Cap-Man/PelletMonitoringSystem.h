#pragma once
#include "System.h"
#include <unordered_map>

class Map;

class PelletMonitoringSystem 
	: public System {
public:
	PelletMonitoringSystem(Manager& manager, Map& map, std::unordered_map<int, int>& pellets);
	~PelletMonitoringSystem();

	void updateEntity(float delta, int entity) override;

private:
	Map& mMap;
	std::unordered_map<int, int>& mPellets;
};

