#include "ResetComponent.h"

ResetComponent::ResetComponent(Point startPosition, int resettableStates)
	: ResetComponent(startPosition, resettableStates, Directions::NONE) {

}

ResetComponent::ResetComponent(Point startPosition, int resettableStates, Directions::Direction startDirection)
	: mStartPosition(startPosition)
	, mResettableStates(resettableStates)
	, mStartDirection(startDirection) {
}

ResetComponent::~ResetComponent() {
}
