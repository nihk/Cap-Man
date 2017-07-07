#include "SpriteGraphicsComponent.h"
#include "Renderer.h"

SpriteGraphicsComponent::SpriteGraphicsComponent(std::unordered_map<AnimationStates::AnimationState, Animation> animations, int initialState)
	: mAnimations(animations)
	, mState(initialState) {
}

SpriteGraphicsComponent::~SpriteGraphicsComponent() {
}

void SpriteGraphicsComponent::update(float delta, int state) {
	if (mState != state) {
		mState = state;
	}

	mAnimations.at(mState).update(delta);
}

void SpriteGraphicsComponent::draw(const Renderer& renderer, const Rect& dest) {
	mAnimations.at(mState).draw(renderer, dest);
}

