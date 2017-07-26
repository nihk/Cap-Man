#include "catch.hpp"
#include "Map.h"
#include "Constants.h"

TEST_CASE("Map 1d index to Point and vice versa is computed") {
	Map map;
	// Assumes the standard 21x23 map
	map.initialize(Metadata::MAP_FILENAME);

	REQUIRE(map.columns() == 21);
	REQUIRE(map.rows() == 23);

	Point loc1 = map.mapLocation(20, false);
	Point loc2 = map.mapLocation(21, false);

	int loc1index = map.mapLocation(loc1, false);
	int loc2index = map.mapLocation(loc2, false);

	REQUIRE(loc1.x() == 20);
	REQUIRE(loc1.y() == 0);
	REQUIRE(loc2.x() == 0);
	REQUIRE(loc2.y() == 1);

	REQUIRE(loc1index == 20);
	REQUIRE(loc2index == 21);
}

TEST_CASE("Navigable tile matches point") {
	Map map;
	// Assumes the standard 21x23 map
	map.initialize(Metadata::MAP_FILENAME);

	int firstPellet = 44;
	Point point = map.mapLocation(firstPellet, false);

	REQUIRE(point.x() == 2);
	REQUIRE(point.y() == 2);
}