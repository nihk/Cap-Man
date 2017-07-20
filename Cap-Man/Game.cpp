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
#include "KeyboardDirectionInputComponent.h"
#include "DirectionAnimationSystem.h"
#include "LastValidDirectionComponent.h"
#include "AStarComponent.h"
#include "PathfindingSystem.h"
#include "PathGoalComponent.h"
#include "WallHuggingSystem.h"
#include "PelletMonitoringSystem.h"
#include "PointsCollectorComponent.h"
#include "WinConditionComponent.h"
#include "ScoreWatcherComponent.h"
#include "ScoreAccumulatorSystem.h"
#include "IdleAnimationComponent.h"
#include "IdleAnimationSystem.h"
#include "TeleportComponent.h"
#include "TeleportSystem.h"
#include "BreadcrumbTrailComponent.h"
#include "BreadcrumbFollowerComponent.h"
#include "BreadcrumbFollowerSystem.h"
#include "BreadcrumbTrailSystem.h"

Game::Game()
	: mShouldQuit(false)
	, mCapMan(-1) {
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
		std::cerr << "Error: Failed to initialize sprite repository" << std::endl;
		return false;
	}

	if (!load()) {
		std::cerr << "Error: Failed to load manager data" << std::endl;
		return false;
	}

	return true;
}

bool Game::load() {
	mManager.createComponentStore<DirectionInputComponent>();
	mManager.createComponentStore<VelocityComponent>();
	mManager.createComponentStore<PhysicsComponent>();
	mManager.createComponentStore<GraphicsComponent>();
	mManager.createComponentStore<LastValidDirectionComponent>();
	mManager.createComponentStore<AStarComponent>();
	mManager.createComponentStore<PathGoalComponent>();
	mManager.createComponentStore<PointsCollectorComponent>();
	mManager.createComponentStore<WinConditionComponent>();
	mManager.createComponentStore<ScoreWatcherComponent>();
	mManager.createComponentStore<IdleAnimationComponent>();
	mManager.createComponentStore<TeleportComponent>();
	mManager.createComponentStore<BreadcrumbTrailComponent>();
	mManager.createComponentStore<BreadcrumbFollowerComponent>();

	// NB: The systems are updated in the order they are added here!
	mManager.addSystem(std::make_shared<SpeedSystem>(mManager));
	mManager.addSystem(std::make_shared<PathfindingSystem>(mManager, mMap));
	mManager.addSystem(std::make_shared<BreadcrumbTrailSystem>(mManager, mMap));
	mManager.addSystem(std::make_shared<BreadcrumbFollowerSystem>(mManager, mMap));
	mManager.addSystem(std::make_shared<WallHuggingSystem>(mManager, mMap));
	mManager.addSystem(std::make_shared<MoveSystem>(mManager));
	mManager.addSystem(std::make_shared<PelletMonitoringSystem>(mManager, mMap, mPellets));
	mManager.addSystem(std::make_shared<DirectionAnimationSystem>(mManager));
	mManager.addSystem(std::make_shared<ScoreAccumulatorSystem>(mManager));
	mManager.addSystem(std::make_shared<TeleportSystem>(mManager));
	mManager.addSystem(std::make_shared<IdleAnimationSystem>(mManager));
	mManager.addSystem(std::make_shared<DrawSystem>(mManager, mRenderer));

	if (!createEntities()) {
		std::cerr << "Error: Failed to create entities" << std::endl;
		return false;
	}

	return true;
}

void Game::update(float delta) {
	mManager.updateSystems(delta);
}

void Game::unload() {
	mManager.clear();
}

void Game::shutdown() {
	unload();
}
