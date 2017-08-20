#pragma once
#include "Component.h"

class SpeedChangeWatcherComponent 
    : public Component<SpeedChangeWatcherComponent> {
public:
    SpeedChangeWatcherComponent();
    ~SpeedChangeWatcherComponent();

    bool speedChanged() const { return mSpeedChanged; }
    void setSpeedChanged(bool changed) { mSpeedChanged = changed; }

private:
    bool mSpeedChanged;
};

