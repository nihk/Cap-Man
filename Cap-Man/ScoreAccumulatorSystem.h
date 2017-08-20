#pragma once

#include "System.h"

class Manager;

class ScoreAccumulatorSystem 
    : public System {
public:
    ScoreAccumulatorSystem(Manager& manager);
    ~ScoreAccumulatorSystem();

    void updateEntity(float delta, int entity) override;
};

