#pragma once
#include "Globals.h"
#include "DirectionInputComponent.h"

class Keyboard;

class KeyboardDirectionInputComponent 
	: public DirectionInputComponent {
public:
	KeyboardDirectionInputComponent(Keyboard& keyboard, Directions::Direction startingDirection);
	~KeyboardDirectionInputComponent();

	KeyboardDirectionInputComponent& operator=(const KeyboardDirectionInputComponent& other);

	Directions::Direction direction() override;

private:
	Keyboard& mKeyboard;
	Directions::Direction mDirection;
};

