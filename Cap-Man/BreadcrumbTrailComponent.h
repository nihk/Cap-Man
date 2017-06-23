#pragma once
#include "Component.h"

class Manager;
class Map;

/**
* Let's an entity leave a trail of "breadcrumbs" that other's can follow
*/
class BreadcrumbTrailComponent
	: public Component<BreadcrumbTrailComponent> {
public:
	BreadcrumbTrailComponent(Map& map);
	~BreadcrumbTrailComponent();

private:
	Map& mMap;
};

