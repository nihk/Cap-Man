#include "PointsComboComponent.h"
#include <algorithm>

const int PointsComboComponent::MAX_MULTIPLIER = 8;  // i.e. 8 * 200 = 1600, the max eaten combo points
const int PointsComboComponent::MIN_MULTIPLIER = 1;

PointsComboComponent::PointsComboComponent()
	: mCurrentCombo(MIN_MULTIPLIER) {
}

PointsComboComponent::~PointsComboComponent() {
}

void PointsComboComponent::addCombo() {
	mCurrentCombo = std::min(MAX_MULTIPLIER, mCurrentCombo * 2);
}
