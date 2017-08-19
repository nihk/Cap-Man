#pragma once
#include <SDL_scancode.h>
#include "Color.h"
#include <string>

namespace Testing {
	static const bool IS_UNIT_TESTING = false;
}

namespace Keys {
	typedef int Key;

	static const Key STOP = 0;
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
	static const Color BLACK(0x00, 0x00, 0x00);
	static const Color WHITE(0xFF, 0xFF, 0xFF);
	static const Color MAGENTA(0xFF, 0x00, 0xFF);
	static const Color BEIGE(0xF8, 0xB0, 0x90);
}

namespace Metadata {
	static const float FPS = 30.0f;
	static const int MAX_FRAME_SKIPS = 6;

	static const std::string SPRITES_FILENAME = "capman_spritesheet.png";
	static const std::string SPRITE_ATLAS_FILENAME = "capman_spriteatlas.xml";
	static const std::string MAP_FILENAME = "capman_map.xml";
	static const std::string GAME_TITLE = "Cap-Man";
}

namespace GameConstants {
	static const int CHARACTER_UNITS_SPEED = 4;  // units/sec
	static const int ANIMATION_FRAME_INTERVAL = 66;  // ms
	static const int CAPMAN_DEATH_ANIMATION_INTERVAL = 132;  // ms
	static const int POWERUP_BLINKING_INTERVAL = 132;  // ms
	static const int ONE_UP_BLINKING_INTERVAL = 198;  // ms
	static const uint8_t NUM_STARTING_LIVES = 2;
	static const int GHOST_DIRECTION_CHANGE_INTERVAL = 1000;  // ms
	static const float GHOST_VULNERABILITY_DURATION = 8.0f * 1000.0f;  // ms
	static const float GHOST_EXPIRING_ANIMATION_TIME = 3.0f * 1000.0f;  // ms
	static const float GHOST_EATEN_PAUSE_DURATION = 650.0f;  // ms
	static const float CAPMAN_DEATH_ANIMATION_FULL_DURATION = 10 * CAPMAN_DEATH_ANIMATION_INTERVAL;  // 11 - 1 frames
	static const int EAT_GHOST_POINTS = 200;
	static const int EAT_PELLET_POINTS = 10;
}

namespace MapLayoutElements {
	static const int INVALID = -1;
	static const int EMPTY_NAVIGABLE_SPACE = 0;
	static const int WALL = 1;
	static const int CAP_MAN = 2;
	static const int INKY = 3;
	static const int CLYDE = 4;
	static const int PINKY = 5;
	static const int BLINKY = 6;
	static const int GHOST_GATE = 7;
	static const int PELLET = 8;
	static const int POWERUP = 9;
	static const int EDGE = 10;
}

namespace AnimationStates {
	typedef int AnimationState;

	static const AnimationState DEFAULT = Directions::NONE;
	static const AnimationState WALK_LEFT = Directions::LEFT;
	static const AnimationState WALK_RIGHT = Directions::RIGHT;
	static const AnimationState WALK_DOWN = Directions::DOWN;
	static const AnimationState WALK_UP = Directions::UP;
	static const AnimationState DEATH = 1 << 4;
	static const AnimationState DEATH_LEFT = 1 << 5;
	static const AnimationState DEATH_RIGHT = 1 << 6;
	static const AnimationState DEATH_UP = 1 << 7;
	static const AnimationState DEATH_DOWN = 1 << 8;
	static const AnimationState VULNERABLE = 1 << 9;
	static const AnimationState VULNERABLE_EXPIRING = 1 << 10;
	static const AnimationState STATIONARY_LEFT = 1 << 11;
	static const AnimationState STATIONARY_RIGHT = 1 << 12;
	static const AnimationState STATIONARY_DOWN = 1 << 13;
	static const AnimationState STATIONARY_UP = 1 << 14;
}