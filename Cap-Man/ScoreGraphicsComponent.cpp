#include "ScoreGraphicsComponent.h"

ScoreGraphicsComponent::ScoreGraphicsComponent(std::unordered_map<int, Sprite>&& numberSprites)
	: mNumberSprites(numberSprites)
	, mScore(0) {
}

ScoreGraphicsComponent::~ScoreGraphicsComponent() {
}

// state is the current accumulated score
void ScoreGraphicsComponent::update(float delta, int state) {
	if (mScore != state) {
		mScore = state;
		mScoreDigits.clear();
		while (state) {
			mScoreDigits.push_back(state % 10);
			state /= 10;
		}
	}
}

void ScoreGraphicsComponent::draw(const Renderer& renderer, const Rect& dest) {
	// Copy
	Rect scoreRect = dest;

	for (auto rit = mScoreDigits.rbegin(); rit != mScoreDigits.rend(); ++rit) {
		Sprite numberSprite = mNumberSprites.at(*rit);
		numberSprite.draw(renderer, scoreRect);

		scoreRect.setLeft(scoreRect.x() + scoreRect.width());
	}
}
