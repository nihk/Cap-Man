#pragma once
#include <cstdint>
#include <SDL.h>
#include "Wrapper.h"

class Color 
	: public Wrapper<SDL_Color> {
public:
	Color();
	Color(uint8_t red, uint8_t green, uint8_t blue);
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
	~Color();

	uint8_t r() const { return mSdlColor.r; }
	uint8_t g() const { return mSdlColor.g; }
	uint8_t b() const { return mSdlColor.b; }
	uint8_t a() const { return mSdlColor.a; }

	const SDL_Color* data() const override { return &mSdlColor; }
	SDL_Color* mutableData() override { return &mSdlColor; }

private:
	SDL_Color mSdlColor;
};

