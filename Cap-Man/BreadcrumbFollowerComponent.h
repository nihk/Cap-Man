#pragma once
#include "Component.h"

// TODO: add a state for following vs running then add previous breadcrumb to the trail component
class BreadcrumbFollowerComponent
	: public Component<BreadcrumbFollowerComponent> {
public:
	BreadcrumbFollowerComponent(int entityToFollow);
	~BreadcrumbFollowerComponent();

	int entityToFollow() const { return mEntityToFollow; }
	bool isFollowing() const { return mIsFollowing; }
	bool isAvoiding() const { return !isFollowing(); }
	void setFollowing() { mIsFollowing = true; }
	void setAvoiding() { mIsFollowing = false; }

private:
	int mEntityToFollow;
	bool mIsFollowing;
};

