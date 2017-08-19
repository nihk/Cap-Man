#pragma once

#include <vector>
#include <unordered_map>
#include "Point.h"
#include "DirectionInputComponent.h"

// I.e. the map of the Cap-Man game, not the classical data structure.
// The map is represented by a one dimensional vector to provide data
// locality.
class Map {
public:
	enum class Scale { SMALL, LARGE };
	enum class StartLocation { CAP_MAN, INKY, BLINKY, PINKY, CLYDE };
	enum class Resize { NONE, UNITS_TO_PIXELS, PIXELS_TO_UNITS };

	Map();
	~Map();

	bool initialize(std::string fileName);

	int mapElement(int x, int y) const;
	int mapElement(const Point& point) const;
	Point startLocation(StartLocation startLocation) const;
	int mapLocation(Point location, bool scaleUnitsToPixels) const;
	Point mapLocation(int layoutIndex, bool scaleUnitsToPixels) const;
	const std::vector<int>& layout() const { return mLayout; }
	int indexOf(int element);
	int rows() const { return mRows; }
	int columns() const { return mColumns; }
	int widthPixels() const;
	int heightPixels() const;
	void setScale(Scale scale) { mActiveScale = scale; }
	Scale scale() const { return mActiveScale; }
	int scaleMultiplier() const { return mScales.at(mActiveScale); }
	int singleUnitPixels() const;
	int unitPixels(int numUnits) const;
	int neighbourElement(Point location, bool scalePixelsToUnits, Directions::Direction direction) const;
	const std::vector<int>& navigableIndices() const { return mNavigableIndices; }

	// TODO: instead of mutating by reference, return new Point (value) instances?
	void scaleUnitsToPixels(int& x, int& y) const;
	void scaleUnitsToPixels(Point& point) const;
	void scalePixelsToUnits(int& x, int& y) const;
	void scalePixelsToUnits(Point& point) const;

private:
	// TODO: Can these be moved elsewhere?
	static const std::string ROOT_XML_TAG;
	static const std::string UNIT_PIXEL_SIZE_XML_TAG;
	static const std::string UNIT_SCALE_XML_TAG;
	static const std::string SMALL_SCALE_XML_TAG;
	static const std::string LARGE_SCALE_XML_TAG;
	static const std::string LAYOUT_XML_TAG;
	static const std::string LAYOUT_ROWS_ATTR;
	static const std::string LAYOUT_COLUMNS_ATTR;
	static const std::string LEGEND_XML_TAG;
	static const std::string ITEM_XML_TAG;
	static const std::string ITEM_KEY_ATTR;
	static const std::string ITEM_VALUE_ATTR;

	std::unordered_map<std::string, int> mLegend;
	int mUnitPixelSize;
	std::unordered_map<Scale, int> mScales;
	Scale mActiveScale;
	std::vector<int> mLayout;
	std::vector<int> mNavigableIndices;
	int mRows;
	int mColumns;  // a.k.a. row-length
};

