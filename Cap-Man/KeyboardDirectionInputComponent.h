#pragma once
#include "Constants.h"
#include "DirectionInputComponent.h"
#include "Keyboard.h"

class KeyboardDirectionInputComponent 
	: public DirectionInputComponent {
public:
	KeyboardDirectionInputComponent(Keyboard& keyboard, Directions::Direction startingDirection);
	KeyboardDirectionInputComponent(const KeyboardDirectionInputComponent& other);
	~KeyboardDirectionInputComponent();

	KeyboardDirectionInputComponent& operator=(const KeyboardDirectionInputComponent& other);

	Directions::Direction direction() override;
	void cancelInput() override { mKeyboard.setRecentKeyDown(Keys::NONE); }

private:
	Keyboard& mKeyboard;
	Directions::Direction mDirection;
};

