#pragma once
#include "GraphicsComponent.h"
#include "Animation.h"
#include <unordered_map>
#include "DirectionInputComponent.h"

class SpriteGraphicsComponent
	: public GraphicsComponent {
public:
	// TODO: add an addAnimation() method instead of passing this to the ctor?
	SpriteGraphicsComponent(std::unordered_map<AnimationStates::AnimationState, Animation> animations, int initialState);
	~SpriteGraphicsComponent();

	void update(float delta, int state) override;
	void draw(Renderer& renderer, const Rect& dest) override;

private:
	std::unordered_map<int, Animation> mAnimations;
	int mState;
};

