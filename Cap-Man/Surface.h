#pragma once
#include <string>
#include <SDL.h>
#include "Wrapper.h"

class Color;

class Surface 
	: Wrapper<SDL_Surface> {
public:
	Surface();
	~Surface();

	bool initialize(const std::string& filePath);
	void setColorKey(const Color& color) const;
	int width() const;
	int height() const;

	const SDL_Surface* data() const override { return mSdlSurface; }
	SDL_Surface* mutableData() override { return mSdlSurface; }

private:
	SDL_Surface* mSdlSurface;
};

