#include "Animation.h"

Animation::Animation(int spriteIntervalMillis)
	: mSpriteIntervalMillis(spriteIntervalMillis)
	, mTimeSpentBetweenSpriteChange(0)
	, mCurrentSpriteIndex(0) {
}

Animation::~Animation() {
	//for (auto& sprite : mSprites) {
	//	delete sprite;
	//}

	//mSprites.clear();
}

void Animation::reset() {
	mTimeSpentBetweenSpriteChange = 0;
	mCurrentSpriteIndex = 0;
}

void Animation::update(float delta) {
	mTimeSpentBetweenSpriteChange += static_cast<int>(delta * 1000.0f /* millis */);

	if (mTimeSpentBetweenSpriteChange >= mSpriteIntervalMillis) {
		mCurrentSpriteIndex = (mCurrentSpriteIndex + 1) % mSprites.size();
		mTimeSpentBetweenSpriteChange = 0;
	}
}

void Animation::draw(Renderer& renderer, const Rectangle& dest) {
	mSprites[mCurrentSpriteIndex].draw(renderer, dest);
}
