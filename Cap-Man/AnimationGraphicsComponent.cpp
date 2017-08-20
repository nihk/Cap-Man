#include "AnimationGraphicsComponent.h"
#include "Renderer.h"

AnimationGraphicsComponent::AnimationGraphicsComponent(std::unordered_map<AnimationStates::AnimationState, Animation>&& animations, AnimationStates::AnimationState initialState)
    : mAnimations(animations)
    , mState(initialState) {
}

AnimationGraphicsComponent::~AnimationGraphicsComponent() {
}

void AnimationGraphicsComponent::update(float delta, int state) {
    if (mState != state) {
        mState = state;
    }

    mAnimations.at(mState).update(delta);
}

void AnimationGraphicsComponent::draw(const Renderer& renderer, const Rect& dest) {
    mAnimations.at(mState).draw(renderer, dest);
}

void AnimationGraphicsComponent::resetAccumulatedTime(AnimationStates::AnimationState animationState) {
    mAnimations.at(animationState).reset();
}

