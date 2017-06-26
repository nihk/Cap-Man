#include "Color.h"
#include "Constants.h"

Color::Color() 
	: Color(Colors::BLACK) {
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
	: Color(red, green, blue, 0xFF) {
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) 
	: mSdlColor(SDL_Color{red, green, blue, alpha}) {
}

Color::~Color() {
}
