#include "Keyboard.h"
#include <SDL.h>

Keyboard::Keyboard()
    : mRecentKeyDown(-1)
    , mKeys(nullptr) {
}

Keyboard::~Keyboard() {
    // I'm not aware of any SDL function to free the keyboard state pointer
}

bool Keyboard::initialize() {
    mKeys = SDL_GetKeyboardState(nullptr);
    return mKeys != nullptr;
}

bool Keyboard::isKeyBeingPressed(Keys::Key key) const {
    return mKeys[key] > 0;
}