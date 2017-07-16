#pragma once
#include "Component.h"

class ScoreWatcherComponent 
	: public Component<ScoreWatcherComponent> {
public:
	ScoreWatcherComponent(int watchedEntity);
	~ScoreWatcherComponent();

	int watchedEntity() const { return mWatchedEntity; }

private:
	int mWatchedEntity;
};

