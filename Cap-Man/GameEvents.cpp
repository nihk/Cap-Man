#include "Game.h"
#include <SDL.h>

void Game::processEvents() {
	while (SDL_PollEvent(&mEvent)) {
		switch (mEvent.type) {
			case SDL_QUIT:
				onQuit();
				break;
			case SDL_KEYDOWN:
				onKeyDown(&mEvent.key);
				break;
			case SDL_KEYUP:
				onKeyUp(&mEvent.key);
				break;
			case SDL_MOUSEBUTTONDOWN:
				onMouseDown(&mEvent.button);
				break;
			case SDL_MOUSEBUTTONUP:
				onMouseUp(&mEvent.button);
				break;
			case SDL_MOUSEMOTION:
				onMouseMotion(&mEvent.motion);
				break;
			case SDL_WINDOWEVENT:
				if (mEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
					onWindowResized(mEvent.window.data1, mEvent.window.data2);
				}
				break;
			default:
				break;
		}
	}
}

void Game::onQuit() {
	mShouldQuit = true;
}

void Game::onKeyDown(const SDL_KeyboardEvent* kbe) {
	int key = kbe->keysym.scancode;
	mKeyboard.setRecentKeyDown(key);

	if (key == SDL_SCANCODE_ESCAPE) {
		mShouldQuit = true;
	} else if (key == SDL_SCANCODE_R) {
		unload();
		load();
	}
}

void Game::onKeyUp(const SDL_KeyboardEvent* kbe) {
	// Stub
}

void Game::onMouseDown(const SDL_MouseButtonEvent* mbe) {
	// Stub
}

void Game::onMouseUp(const SDL_MouseButtonEvent* mbe) {
	// Stub
}

void Game::onMouseMotion(const SDL_MouseMotionEvent* mme) {
	// Stub
}

void Game::onWindowResized(int w, int h) {
	// TODO: Remove this
	//mWindow.setDimens(w, h);
}
