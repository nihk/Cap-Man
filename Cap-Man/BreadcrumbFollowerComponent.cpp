#include "BreadcrumbFollowerComponent.h"

BreadcrumbFollowerComponent::BreadcrumbFollowerComponent(int entityToFollow) 
    : mEntityToFollow(entityToFollow)
    , mIsFollowing(true) {
}

BreadcrumbFollowerComponent::~BreadcrumbFollowerComponent() {
}
