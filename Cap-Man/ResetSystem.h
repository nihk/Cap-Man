#pragma once
#include "System.h"
#include "Game.h"

class Map;

class ResetSystem 
    : public System {
public:
    ResetSystem(Manager& manager, int& state, std::unordered_set<int>& consumedEntities);
    ~ResetSystem();

    size_t updateEntities(float delta) override;
    void updateEntity(float delta, int entity) override;

private:
    int& mGameState;
    std::unordered_set<int>& mConsumedEntities;
};

