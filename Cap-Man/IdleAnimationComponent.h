#pragma once
#include "Component.h"

// Used on entities that don't have velocities but still animate sprites
class IdleAnimationComponent
	: public Component<IdleAnimationComponent> {
public:
	IdleAnimationComponent();
	IdleAnimationComponent(int state);
	~IdleAnimationComponent();

	int state() const { return mState; }
	void setState(int state) { mState = state; }

private:
	// The state its animation should be in
	int mState;
};

