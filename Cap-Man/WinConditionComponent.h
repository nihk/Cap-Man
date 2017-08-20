#pragma once
#include "Component.h"

class WinConditionComponent 
    : public Component<WinConditionComponent> {
public:
    WinConditionComponent();
    ~WinConditionComponent();

    bool hasWon() const { return mHasWon; }
    void reset();
    void setWon();
    int numGamesWon() const { return mNumGamesWon; }
    void nextRound();
    int numPelletsEaten() const { return mNumPelletsEaten; }
    void addPelletEaten() { ++mNumPelletsEaten; }

private:
    bool mHasWon;
    int mNumGamesWon;
    int mNumPelletsEaten;
};

