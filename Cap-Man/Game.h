#pragma once

#include <SDL.h>
#include "Manager.h"
#include "Window.h"
#include "Renderer.h"
#include "Color.h"
#include "Keyboard.h"
#include "Map.h"

class Game {
public:
	Game();
	~Game();

	bool		run();

private:
	bool		mShouldQuit;

	Window		mWindow;
	Renderer	mRenderer;
	Keyboard	mKeyboard;
	Color		mBackgroundColor;
	SDL_Event	mEvent;

	Manager		mManager;
	Map			mMap;

	bool		initialize();
	void		load();
	void		unload();
	void		shutdown();
	void		onQuit();
	void		update(float delta);

	// TODO: Can/should these be wrapped efficiently into their own class(es)?
	void		processEvents();
	void		onKeyDown(const SDL_KeyboardEvent* kbe);
	void		onKeyUp(const SDL_KeyboardEvent* kbe);
	void		onMouseDown(const SDL_MouseButtonEvent* mbe);
	void		onMouseUp(const SDL_MouseButtonEvent* mbe);
	void		onMouseMotion(const SDL_MouseMotionEvent* mme);
	void		onWindowResized(int w, int h);
};

