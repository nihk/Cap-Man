#include "IdleAnimationComponent.h"

IdleAnimationComponent::IdleAnimationComponent() 
	: IdleAnimationComponent(0) {
}

IdleAnimationComponent::IdleAnimationComponent(int state)
	: mState(state) {
}

IdleAnimationComponent::~IdleAnimationComponent() {
}
