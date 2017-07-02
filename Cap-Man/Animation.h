#pragma once
#include <vector>
#include "Sprite.h"
#include "Drawable.h"

class Rect;
class Renderer;

class Animation 
	: public Drawable {
public:
	Animation();
	Animation(int spriteIntervalMillis);
	~Animation();

	void addSprite(Sprite sprite) { mSprites.push_back(sprite); }

	void reset();
	void update(float delta);
	void draw(Renderer& renderer, const Rect& dest) override;

private:
	// Ideally this should be some factor of the delta update millis
	unsigned mSpriteIntervalMillis;
	unsigned mTimeSpentBetweenSpriteChange;
	unsigned mCurrentSpriteIndex;
	std::vector<Sprite> mSprites;
};

