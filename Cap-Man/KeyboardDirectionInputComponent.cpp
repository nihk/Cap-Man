#include "KeyboardDirectionInputComponent.h"
#include "Keyboard.h"

KeyboardDirectionInputComponent::KeyboardDirectionInputComponent(Keyboard& keyboard, Directions::Direction startingDirection)
	: mKeyboard(keyboard) 
	, mDirection(startingDirection) {
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
		default:			/* mDirection = Directions::NONE;	*/ break;
	}

	return mDirection;
}
