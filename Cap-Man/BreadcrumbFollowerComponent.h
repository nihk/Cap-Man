#pragma once
#include "Component.h"

// TODO: add a state for following vs running then add previous breadcrumb to the trail component
class BreadcrumbFollowerComponent
    : public Component<BreadcrumbFollowerComponent> {
public:
    BreadcrumbFollowerComponent(int entityToFollow);
    ~BreadcrumbFollowerComponent();

    int entityToFollow() const { return mEntityToFollow; }

private:
    int mEntityToFollow;
    bool mIsFollowing;
};

