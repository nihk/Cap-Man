#pragma once
#include "System.h"

// Pauses other systems, except essential ones that draw
class PauseSystem 
	: public System {
public:
	PauseSystem(Manager& manager);
	~PauseSystem();

	void updateEntity(float delta, int entity) override;
	bool areSystemsPaused() const { return mAreSystemsPaused; }
	void setSystemsPaused(bool shouldPause) { mAreSystemsPaused = shouldPause; }

private:
	const static bool PAUSE;
	const static bool UNPAUSE;

	void togglePause(bool shouldPause) const;

	bool mAreSystemsPaused;
};

