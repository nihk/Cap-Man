#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "Globals.h"
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

	if (!mWindow.initialize(mMap.width(), mMap.height())) {
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

	load();

	return true;
}

void Game::load() {
	// TODO: Move this into a factory class
	mManager.createComponentStore<DirectionInputComponent>();
	mManager.createComponentStore<VelocityComponent>();
	mManager.createComponentStore<PhysicsComponent>();
	mManager.createComponentStore<GraphicsComponent>();

	// Order matters here
	mManager.addSystem(std::make_shared<SpeedSystem>(mManager));
	mManager.addSystem(std::make_shared<MoveSystem>(mManager));
	mManager.addSystem(std::make_shared<DrawSystem>(mManager, mRenderer));

	int pacman = mManager.createEntity();

	mManager.addComponent(pacman, KeyboardDirectionInputComponent(mKeyboard, Directions::RIGHT));
	mManager.addComponent(pacman, VelocityComponent(Velocity(GameConstants::CHARACTER_SPEED, 0.0f), GameConstants::CHARACTER_SPEED));
	mManager.addComponent(pacman, PhysicsComponent(50, 50, mMap.unitFactor(), mMap.unitFactor()));
	mManager.addComponent(pacman, ColorGraphicsComponent(Colors::MAGENTA));

	mManager.registerEntity(pacman);
}

void Game::update(float delta) {
	mRenderer.setDrawColor(mBackgroundColor);
	mRenderer.clear();

	mManager.updateSystems(delta);

	mRenderer.present();
}

void Game::unload() {
	// Stub
}

void Game::shutdown() {
	unload();
}
