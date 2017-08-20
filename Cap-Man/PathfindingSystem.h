#pragma once
#include "System.h"

class Map;

class PathfindingSystem 
    : public System {
public:
    PathfindingSystem(Manager& manager, Map& map);
    ~PathfindingSystem();

    void updateEntity(float delta, int entity) override;

private:
    Map& mMap;
};

