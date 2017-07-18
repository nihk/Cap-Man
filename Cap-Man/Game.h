#pragma once

#include <SDL.h>
#include "Manager.h"
#include "Window.h"
#include "Renderer.h"
#include "Color.h"
#include "Keyboard.h"
#include "Map.h"
#include "SpriteRepository.h"
#include <stack>

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
	SpriteRepository	mSpriteRepository;

	int			mCapMan;
	std::unordered_map<int /* map layout index */, int /* entity id */> mPellets;
	std::unordered_map<int /* map layout index */, int /* entity id */> mPowerups;
	std::stack<int> mLifeEntities;

	bool		initialize();
	bool load();
	bool		createEntities();
	void		unload();
	void		shutdown();
	void		onQuit();
	void		update(float delta);

	// TODO: Can/should these be wrapped into their own class(es)?
	void		processEvents();
	void		onKeyDown(const SDL_KeyboardEvent* kbe);
	void		onKeyUp(const SDL_KeyboardEvent* kbe);
	void		onMouseDown(const SDL_MouseButtonEvent* mbe);
	void		onMouseUp(const SDL_MouseButtonEvent* mbe);
	void		onMouseMotion(const SDL_MouseMotionEvent* mme);
	void		onWindowResized(int w, int h);
};

