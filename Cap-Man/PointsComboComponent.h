#pragma once
#include "Component.h"

// Comboing successive ghost eating, e.g. 200 points, 400 points, 800 points, etc. successively
class PointsComboComponent 
    : public Component<PointsComboComponent> {
public:
    PointsComboComponent();
    ~PointsComboComponent();

    int currentCombo() const { return mCurrentCombo; }
    void addCombo();
    void resetCombo() { mCurrentCombo = MIN_MULTIPLIER; }


private:
    static const int MAX_MULTIPLIER;
    static const int MIN_MULTIPLIER;
    int mCurrentCombo;
};

