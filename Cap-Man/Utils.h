#pragma once
#include "Constants.h"

namespace DirectionUtils {
	inline Directions::Direction turnLeft(Directions::Direction currentDirection) {
		switch (currentDirection) {
			case Directions::UP: return Directions::LEFT;
			case Directions::LEFT: return Directions::DOWN;
			case Directions::DOWN: return Directions::RIGHT;
			case Directions::RIGHT: return Directions::UP;
			default: return Directions::NONE;
		}
	}

	inline Directions::Direction turnRight(Directions::Direction currentDirection) {
		switch (currentDirection) {
			case Directions::UP: return Directions::RIGHT;
			case Directions::LEFT: return Directions::UP;
			case Directions::DOWN: return Directions::LEFT;
			case Directions::RIGHT: return Directions::DOWN;
			default: return Directions::NONE;
		}
	}

	inline Directions::Direction turnBack(Directions::Direction currentDirection) {
		switch (currentDirection) {
			case Directions::UP: return Directions::DOWN;
			case Directions::LEFT: return Directions::RIGHT;
			case Directions::DOWN: return Directions::UP;
			case Directions::RIGHT: return Directions::LEFT;
			default: return Directions::NONE;
		}
	}
}
