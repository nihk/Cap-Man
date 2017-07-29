#include "WinConditionComponent.h"

WinConditionComponent::WinConditionComponent()
	: mHasWon(false)
	, mNumGamesWon(0) {
}

WinConditionComponent::~WinConditionComponent() {
}

void WinConditionComponent::reset() {
	mHasWon = false;
	mNumGamesWon = 0;
}

void WinConditionComponent::setWon() {
	mHasWon = true;
	++mNumGamesWon;
}

void WinConditionComponent::nextRound() {
	mHasWon = false;
}
