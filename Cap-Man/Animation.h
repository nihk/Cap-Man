#pragma once
#include <vector>
#include "Sprite.h"
#include "Drawable.h"

class Rectangle;
class Renderer;

class Animation 
	: public Drawable {
public:
	Animation(int spriteIntervalMillis);
	~Animation();

	// TODO: unique_ptr instead?
	void addSprite(Sprite sprite) { mSprites.push_back(sprite); }

	void reset();
	void update(float delta);
	void draw(Renderer& renderer, const Rectangle& dest) override;

private:
	unsigned mSpriteIntervalMillis;
	unsigned mTimeSpentBetweenSpriteChange;
	unsigned mCurrentSpriteIndex;
	// TODO: unique_ptr?
	std::vector<Sprite> mSprites;
};

