#pragma once
#include "GraphicsComponent.h"
#include "Sprite.h"
#include <unordered_map>

class ScoreGraphicsComponent 
	: public GraphicsComponent {
public:
	ScoreGraphicsComponent(std::unordered_map<int, Sprite>&& numberSprites);
	~ScoreGraphicsComponent();

	void update(float delta, int state) override;
	void draw(const Renderer& renderer, const Rect& dest) override;

private:
	std::unordered_map<int, Sprite> mNumberSprites;
	int mScore;
	std::vector<int> mScoreDigits;
};

