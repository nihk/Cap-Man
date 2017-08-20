#pragma once
#include "Component.h"
#include "AnimationGraphicsComponent.h"

class EatableComponent 
    : public Component<EatableComponent> {
public:
    EatableComponent(int eaterEntity);
    ~EatableComponent();

    int eaterEntity() const { return mEaterEntity; }
    bool isEaten() const { return mEaten; }
    void setEaten(bool eaten) { mEaten = eaten; }
    void update(float delta);
    AnimationStates::AnimationState eatenPointsAnimationState() const { return mEatenPointsAnimationState; }
    void setEatenPointsAnimationState(AnimationStates::AnimationState state) { mEatenPointsAnimationState = state; }

private:
    int mEaterEntity;
    bool mEaten;
    float mAccumulatedTime;
    float mEatenDuration;
    AnimationStates::AnimationState mEatenPointsAnimationState;
};

