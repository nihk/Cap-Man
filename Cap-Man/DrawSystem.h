#pragma once
#include "System.h"

class Renderer;

class DrawSystem
    : public System {
public:
    DrawSystem(Manager& manager, Renderer& renderer);
    ~DrawSystem();

    size_t updateEntities(float delta) override;
    void updateEntity(float delta, int entity) override;

private:
    Renderer& mRenderer;
};

