#pragma once
#include <SDL_scancode.h>
#include "Color.h"
#include <string>

namespace Testing {
	static const bool IS_UNIT_TESTING = false;
}

namespace Keys {
	typedef int Key;

	static const Key UP = SDL_SCANCODE_UP;
	static const Key DOWN = SDL_SCANCODE_DOWN;
	static const Key LEFT = SDL_SCANCODE_LEFT;
	static const Key RIGHT = SDL_SCANCODE_RIGHT;
	static const Key W = SDL_SCANCODE_W;
	static const Key A = SDL_SCANCODE_A;
	static const Key S = SDL_SCANCODE_S;
	static const Key D = SDL_SCANCODE_D;
}

namespace Directions {
	typedef int Direction;

	static const Direction NONE = 0;
	static const Direction UP = 1;
	static const Direction DOWN = 1 << 1;
	static const Direction LEFT = 1 << 2;
	static const Direction RIGHT = 1 << 3;
}

namespace Colors {
	static const Color BLACK(0x00, 0x00, 0x00, 0xFF);
	static const Color WHITE(0xFF, 0xFF, 0xFF, 0xFF);
	static const Color MAGENTA(0xFF, 0x00, 0xFF, 0xFF);
}

namespace Metadata {
	const float FPS = 30.0f;
	const int MAX_FRAME_SKIPS = 6;

	const std::string SPRITES_FILENAME = "capman_spritesheet.png";
	const std::string SPRITE_ATLAS_FILENAME = "capman_spriteatlas.xml";
	const std::string MAP_FILENAME = "capman_map.xml";
	const std::string GAME_TITLE = "Cap-Man";
}

namespace GameConstants {
	// TODO: Minimum movement speed at 60fps is 60px/s. Need to make an FPS independent velocity that can travel under 60px/s
	const int CHARACTER_UNITS_SPEED = 4;  // units/sec
	const int ANIMATION_FRAME_INTERVAL = 50;  // ms
}

namespace AnimationStates {
	typedef int AnimationState;

	const AnimationState DEFAULT = Directions::NONE;
	const AnimationState WALK_LEFT = Directions::LEFT;
	const AnimationState WALK_RIGHT = Directions::RIGHT;
	const AnimationState WALK_DOWN = Directions::DOWN;
	const AnimationState WALK_UP = Directions::UP;
	const AnimationState DEATH = 1 << 4;
	const AnimationState VULNERABLE = 1 << 5;
}