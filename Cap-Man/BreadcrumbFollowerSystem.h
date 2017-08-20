#pragma once

#include "System.h"
#include "Constants.h"

class Point;
class Map;

class BreadcrumbFollowerSystem 
    : public System {
public:
    BreadcrumbFollowerSystem(Manager& manager, Map& map);
    ~BreadcrumbFollowerSystem();

    void updateEntity(float delta, int entity) override;

private:
    static Directions::Direction nextDirection(const Point& current, const Point& dest);

    Map& mMap;
};

