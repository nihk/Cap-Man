#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "Constants.h"
#include <SDL_image.h>
#include "VelocityComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "DirectionInputComponent.h"
#include "SpeedSystem.h"
#include "MoveSystem.h"
#include "DrawSystem.h"
#include "ColorGraphicsComponent.h"
#include "KeyboardDirectionInputComponent.h"
#include "DirectionAnimationSystem.h"
#include "WallPathingSystem.h"
#include "DirectionValidatorComponent.h"

Game::Game()
	: mShouldQuit(false) {
}

Game::~Game() {
	SDL_Quit();
}

bool Game::run() {
	if (!initialize()) {
		std::cerr << "Error: Game initialization failed" << std::endl;
		return false;
	}

	const float deltaF = 1.0f / Metadata::FPS;
	const unsigned deltaMs = static_cast<int>(deltaF * 1000.0f /* millis */);
	unsigned currentTime = SDL_GetTicks();
	unsigned gameTime = currentTime;

	while (!mShouldQuit) {
		processEvents();

		int updates = 0;
		while ((currentTime = SDL_GetTicks()) > gameTime && ++updates < Metadata::MAX_FRAME_SKIPS) {
			gameTime += deltaMs;
			update(deltaF);
		}
	}

	shutdown();

	return true;
}

bool Game::initialize() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error: Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) < 0) {
		std::cerr << "Error: Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
		return false;
	}

	if (!mMap.initialize(Metadata::MAP_FILENAME)) {
		std::cerr << "Error: Failed to initialize map" << std::endl;
		return false;
	}

	if (!mWindow.initialize(mMap.widthPixels(), mMap.heightPixels())) {
		std::cerr << "Error: Failed to initialize window: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!mRenderer.initialize(mWindow)) {
		std::cerr << "Error: Failed to initialize renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!mKeyboard.initialize()) {
		std::cerr << "Error: Failed to initialize keyboard: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!mSpriteRepository.initialize(mRenderer, Metadata::SPRITES_FILENAME, Metadata::SPRITE_ATLAS_FILENAME)) {
		std::cerr << "Error: Failed to initialize sprite repository: " << std::endl;
		return false;
	}

	load();

	return true;
}

void Game::load() {
	mManager.createComponentStore<DirectionInputComponent>();
	mManager.createComponentStore<VelocityComponent>();
	mManager.createComponentStore<PhysicsComponent>();
	mManager.createComponentStore<GraphicsComponent>();
	mManager.createComponentStore<DirectionValidatorComponent>();

	// Order matters here
	mManager.addSystem(std::make_shared<SpeedSystem>(mManager));
	mManager.addSystem(std::make_shared<WallPathingSystem>(mManager, mMap));
	mManager.addSystem(std::make_shared<MoveSystem>(mManager));
	mManager.addSystem(std::make_shared<DirectionAnimationSystem>(mManager));
	mManager.addSystem(std::make_shared<DrawSystem>(mManager, mRenderer));

	if (!createEntities()) {
		std::cerr << "Error: Failed to create entities: " << std::endl;
		return;
	}
}

void Game::update(float delta) {
	mRenderer.setDrawColor(mBackgroundColor);
	mRenderer.clear();

	mManager.updateSystems(delta);

	mRenderer.present();
}

void Game::unload() {
	// TODO: Remove all entities from mManager
}

void Game::shutdown() {
	unload();
}
