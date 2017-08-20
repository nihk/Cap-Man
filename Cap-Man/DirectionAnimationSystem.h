#pragma once
#include "System.h"

class DirectionAnimationSystem 
    : public System {
public:
    DirectionAnimationSystem(Manager& manager);
    ~DirectionAnimationSystem();

    void updateEntity(float delta, int entity) override;
};

