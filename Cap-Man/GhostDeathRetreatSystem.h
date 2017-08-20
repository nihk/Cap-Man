#pragma once
#include "System.h"
#include "Map.h"

class GhostDeathRetreatSystem 
    : public System {
public:
    GhostDeathRetreatSystem(Manager& manager, Map& map);
    ~GhostDeathRetreatSystem();

    void updateEntity(float delta, int entity) override;

private:
    Map& mMap;
};

