#pragma once
#include "System.h"
#include <unordered_map>
#include <unordered_set>

class Map;

class PowerupMonitoringSystem 
    : public System {
public:
    PowerupMonitoringSystem(Manager& manager, Map& map, std::unordered_map<int, int>& powerups, 
        std::unordered_set<int>& consumedEntities, std::unordered_set<int>& ghosts);
    ~PowerupMonitoringSystem();

    void updateEntity(float delta, int entity) override;

private:
    void turnGhostsVulnerable() const;
    bool resetGhostVulnerabilitySpeed() const;

    Map& mMap;
    std::unordered_map<int, int>& mPowerups;
    std::unordered_set<int>& mConsumedEntities;
    std::unordered_set<int>& mGhosts;
};

