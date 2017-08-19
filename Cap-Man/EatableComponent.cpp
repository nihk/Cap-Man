#include "EatableComponent.h"
#include "Constants.h"

EatableComponent::EatableComponent(int eaterEntity)
	: mEaterEntity(eaterEntity)
	, mEaten(false)
	, mAccumulatedTime(0.0f)
	, mEatenDuration(GameConstants::GHOST_EATEN_PAUSE_DURATION)
	, mEatenPointsAnimationState(AnimationStates::EATEN_200) {
}

EatableComponent::~EatableComponent() {
}

void EatableComponent::update(float delta) {
	if (mEaten) {
		mAccumulatedTime += delta * 1000.0f;
		if (mAccumulatedTime >= mEatenDuration) {
			mEaten = false;
			mAccumulatedTime = 0.0f;
		}
	}
}
