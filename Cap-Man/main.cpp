#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <SDL.h>
#include "catch.hpp"
#include "Game.h"
#include "Constants.h"

int main(int argc, char** argv) {
	if (Testing::IS_UNIT_TESTING) {
		int result = Catch::Session().run(argc, argv);
		return (result < 0xff ? result : 0xff);
	} else {
		Game game;

		if (!game.run()) {
			std::cerr << "Error: Game failed to run" << std::endl;
			return 1;
		}
		return 0;
	}
}
