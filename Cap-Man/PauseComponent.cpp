#include "PauseComponent.h"

PauseComponent::PauseComponent() 
	: PauseComponent(false, 0.0f) {
}

PauseComponent::PauseComponent(bool initialPauseState, float initialPauseDuration)
	: mShouldPause(initialPauseState)
	, mPauseDurationMillis(initialPauseDuration)
	, mAccumulatedPauseTimeMillis(0.0f) {
}

PauseComponent::~PauseComponent() {
}

bool PauseComponent::shouldPause() const {
	return mShouldPause && mAccumulatedPauseTimeMillis < mPauseDurationMillis;
}

void PauseComponent::setShouldPause(bool shouldPause, float pauseDuration) {
	mShouldPause = shouldPause;
	mPauseDurationMillis = pauseDuration;
	mAccumulatedPauseTimeMillis = 0.0f;
}

void PauseComponent::update(float delta) {
	if (mShouldPause) {
		mAccumulatedPauseTimeMillis += delta * 1000;

		if (mAccumulatedPauseTimeMillis >= mPauseDurationMillis) {
			reset();
		}
	}
}

void PauseComponent::reset() {
	mShouldPause = false;
	mAccumulatedPauseTimeMillis = 0.0f;
	mPauseDurationMillis = 0.0f;
}
