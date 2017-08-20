#include "PseudoRandomDirectionComponent.h"

PseudoRandomDirectionComponent::PseudoRandomDirectionComponent(int directionChangeIntervalMillis) 
        : mDirectionChangeIntervalMillis(directionChangeIntervalMillis)
        , mAccumulatedIntervalTime(0.0f) {
    mDirections.push_back(Directions::DOWN);
    mDirections.push_back(Directions::UP);
    mDirections.push_back(Directions::LEFT);
    mDirections.push_back(Directions::RIGHT);
}

PseudoRandomDirectionComponent::~PseudoRandomDirectionComponent() {
}

Directions::Direction PseudoRandomDirectionComponent::getRandomDirectionExcept(Directions::Direction currentDirection) const {
    std::vector<int> potentialNewDirections;
    Directions::Direction opposite = oppositeDirection(currentDirection);

    for (int i : mDirections) {
        if (i != currentDirection && i != opposite) {
            potentialNewDirections.push_back(i);
        }
    }

    int randomIndex = rand() % potentialNewDirections.size();
    return potentialNewDirections.at(randomIndex);
}

void PseudoRandomDirectionComponent::update(float delta) {
    mAccumulatedIntervalTime += delta * 1000;
}

bool PseudoRandomDirectionComponent::canChangeDirection() const {
    return mAccumulatedIntervalTime >= mDirectionChangeIntervalMillis;
}

void PseudoRandomDirectionComponent::resetAccumulatorInterval() {
    mAccumulatedIntervalTime = 0.0f;
}

Directions::Direction PseudoRandomDirectionComponent::oppositeDirection(Directions::Direction direction) {
    switch (direction) {
        case Directions::UP: return Directions::DOWN;
        case Directions::DOWN: return Directions::UP;
        case Directions::LEFT: return Directions::RIGHT;
        case Directions::RIGHT: return Directions::LEFT;
        default: return Directions::NONE;
    }
}
