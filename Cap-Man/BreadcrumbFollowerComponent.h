#pragma once
#include "Component.h"

class BreadcrumbFollowerComponent
	: public Component<BreadcrumbFollowerComponent> {
public:
	BreadcrumbFollowerComponent(int entityToFollow);
	~BreadcrumbFollowerComponent();

	int entityToFollow() const { return mEntityToFollow; }

private:
	int mEntityToFollow;
};

