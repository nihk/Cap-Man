#pragma once
#include "GraphicsComponent.h"
#include "Animation.h"
#include <unordered_map>
#include "DirectionInputComponent.h"

class AnimationGraphicsComponent
    : public GraphicsComponent {
public:
    // TODO: add an addAnimation() method instead of passing this to the ctor?
    AnimationGraphicsComponent(std::unordered_map<AnimationStates::AnimationState, Animation>&& animations, AnimationStates::AnimationState initialState);
    ~AnimationGraphicsComponent();

    void update(float delta, int state) override;
    void draw(const Renderer& renderer, const Rect& dest) override;
    void resetAccumulatedTime(AnimationStates::AnimationState animationState);
    AnimationStates::AnimationState state() const { return mState; }

private:
    std::unordered_map<AnimationStates::AnimationState, Animation> mAnimations;
    AnimationStates::AnimationState mState;
};

