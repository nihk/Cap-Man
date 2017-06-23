#include "Window.h"
#include "Globals.h"
#include <SDL.h>

Window::Window() 
	: mSdlWindow(nullptr)
	, mWidth(-1)
	, mHeight(-1) {
}

Window::~Window() {
	SDL_DestroyWindow(mSdlWindow);
}

bool Window::initialize(int width, int height) {
	mWidth = width;
	mHeight = height;

	mSdlWindow = SDL_CreateWindow(Metadata::GAME_TITLE.data(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		mWidth, mHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	return mSdlWindow != nullptr;
}
