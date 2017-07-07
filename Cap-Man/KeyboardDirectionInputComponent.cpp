#include "KeyboardDirectionInputComponent.h"
#include "Keyboard.h"

KeyboardDirectionInputComponent::KeyboardDirectionInputComponent(Keyboard& keyboard, Directions::Direction startingDirection)
		: DirectionInputComponent(startingDirection)
		, mKeyboard(keyboard) {
	KeyboardDirectionInputComponent::setDirection(startingDirection);
}

KeyboardDirectionInputComponent::KeyboardDirectionInputComponent(const KeyboardDirectionInputComponent& other)
	: KeyboardDirectionInputComponent(other.mKeyboard, other.mDirection) {
}

KeyboardDirectionInputComponent::~KeyboardDirectionInputComponent() {
}

KeyboardDirectionInputComponent& KeyboardDirectionInputComponent::operator=(const KeyboardDirectionInputComponent& other) {
	this->mKeyboard = other.mKeyboard;
	return *this;
}

Directions::Direction KeyboardDirectionInputComponent::direction() {
	int recentKeyDown = mKeyboard.getRecentKeyDown();

	switch (recentKeyDown) {
		case Keys::UP:
		case Keys::W:		mDirection = Directions::UP;	break;
		case Keys::DOWN:
		case Keys::S:		mDirection = Directions::DOWN;	break;
		case Keys::LEFT:
		case Keys::A:		mDirection = Directions::LEFT;	break;
		case Keys::RIGHT:
		case Keys::D:		mDirection = Directions::RIGHT;	break;
		case Keys::STOP:	mDirection = Directions::NONE;	break;
		default:			/* do nothing */				break;
	}

	return mDirection;
}

void KeyboardDirectionInputComponent::setDirection(Directions::Direction direction) {
	mKeyboard.setRecentKeyDown(direction);
}
