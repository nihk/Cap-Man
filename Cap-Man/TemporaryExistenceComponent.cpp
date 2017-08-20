#include "TemporaryExistenceComponent.h"

TemporaryExistenceComponent::TemporaryExistenceComponent(float howLong)
    : mWasRemoved(false)
    , mExists(true)
    , mExistenceDuration(howLong)
    , mAccumulatedTime(0.0f) {
}

TemporaryExistenceComponent::~TemporaryExistenceComponent() {
}

void TemporaryExistenceComponent::update(float delta) {
    if (mExists) {
        mAccumulatedTime += delta * 1000.0f;
        if (mAccumulatedTime >= mExistenceDuration) {
            mExists = false;
        }
    }
}

void TemporaryExistenceComponent::reset() {
    mExists = true;
    mAccumulatedTime = 0.0f;
}
