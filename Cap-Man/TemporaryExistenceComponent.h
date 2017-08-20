#pragma once
#include "Component.h"

class TemporaryExistenceComponent 
    : public Component<TemporaryExistenceComponent> {
public:
    TemporaryExistenceComponent(float howLong);
    ~TemporaryExistenceComponent();

    void update(float delta);
    bool exists() const { return mExists; }
    bool wasRemoved() const { return mWasRemoved; }
    void setWasRemoved(bool wasRemoved) { mWasRemoved = wasRemoved; }
    void reset();

private:
    bool mWasRemoved;
    bool mExists;
    float mExistenceDuration;
    float mAccumulatedTime;
};

