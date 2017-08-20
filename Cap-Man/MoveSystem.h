#pragma once

#include "System.h"

class MoveSystem
    : public System {
public:
    MoveSystem(Manager& manager);
    ~MoveSystem();

    void updateEntity(float delta, int entity) override;
};

