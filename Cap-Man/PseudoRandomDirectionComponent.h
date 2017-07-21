#pragma once
#include "Component.h"
#include "Constants.h"
#include <vector>

class PseudoRandomDirectionComponent
	: public Component<PseudoRandomDirectionComponent> {
public:
	PseudoRandomDirectionComponent(int directionChangeIntervalMillis);
	~PseudoRandomDirectionComponent();

	Directions::Direction getRandomDirectionExcept(Directions::Direction direction) const;
	void update(float delta);
	bool canChangeDirection() const;
	// This should always be called after getRandomDirectionExcept()
	void resetAccumulatorInterval();

private:
	static Directions::Direction oppositeDirection(Directions::Direction direction);

	std::vector<Directions::Direction> mDirections;
	int mDirectionChangeIntervalMillis;
	float mAccumulatedIntervalTime;
};

