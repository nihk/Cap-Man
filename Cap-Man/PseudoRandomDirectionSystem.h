#pragma once
#include "System.h"
#include "Map.h"

class PseudoRandomDirectionSystem
    : public System {
public:
    PseudoRandomDirectionSystem(Manager& manager, Map& map);
    ~PseudoRandomDirectionSystem();

    void updateEntity(float delta, int entity) override;

private:
    Map& mMap;
};

