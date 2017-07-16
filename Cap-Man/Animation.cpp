#include "Animation.h"

Animation::Animation() 
	: Animation(0) {
}

Animation::Animation(int spriteIntervalMillis)
	: mSpriteIntervalMillis(spriteIntervalMillis)
	, mTimeSpentBetweenSpriteChange(0.0f)
	, mCurrentSpriteIndex(0) {
}

Animation::~Animation() {
}

void Animation::reset() {
	mTimeSpentBetweenSpriteChange = 0.0f;
	mCurrentSpriteIndex = 0;
}

void Animation::update(float delta) {
	mTimeSpentBetweenSpriteChange += delta * 1000.0f /* millis */;

	if (mTimeSpentBetweenSpriteChange >= mSpriteIntervalMillis) {
		mCurrentSpriteIndex = (mCurrentSpriteIndex + 1) % mSprites.size();
		mTimeSpentBetweenSpriteChange = 0.0f;
	}
}

void Animation::draw(const Renderer& renderer, const Rect& dest) {
	mSprites.at(mCurrentSpriteIndex).draw(renderer, dest);
}
