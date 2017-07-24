#pragma once
#include "Component.h"

class PauseComponent 
	: public Component<PauseComponent> {
public:
	PauseComponent();
	PauseComponent(bool initialPauseState, float initialPauseDurationMillis);
	~PauseComponent();

	bool shouldPause() const;
	void setShouldPause(bool shouldPause, float pauseDuration);
	void update(float delta);

private:
	void reset();

	bool mShouldPause;
	float mPauseDurationMillis;
	float mAccumulatedPauseTimeMillis;
};

