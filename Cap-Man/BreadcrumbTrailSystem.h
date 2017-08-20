#pragma once

#include "System.h"

class Map;

class BreadcrumbTrailSystem 
    : public System {
public:
    BreadcrumbTrailSystem(Manager& manager, Map& map);
    ~BreadcrumbTrailSystem();

    void updateEntity(float delta, int entity) override;

private:
    Map& mMap;
};

