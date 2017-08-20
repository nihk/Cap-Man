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
    void setDirection(Directions::Direction direction) override;

private:
    Keyboard& mKeyboard;
};

