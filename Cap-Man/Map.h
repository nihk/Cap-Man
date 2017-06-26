#pragma once

#include <vector>
#include <unordered_map>
#include "Point.h"

// I.e. the map of the Cap-Man game, not the classical data structure.
// The map is represented by a one dimensional vector to provide data
// locality.
class Map {
public:
	enum class Scale { SMALL, MEDIUM, LARGE };
	enum class StartLocation { CAP_MAN, INKY, BLINKY, PINKY, CLYDE };

	Map();
	~Map();

	bool initialize(std::string fileName);

	int getMapElement(int x, int y);
	//Point getStartLocation(StartLocation startLocation) const;
	int indexOf(int element);
	int rows() const { return mRows; }
	int columns() const { return mColumns; }
	int widthPixels() const;
	int heightPixels() const;
	void setScale(Scale scale) { mActiveScale = scale; }
	Scale scale() const { return mActiveScale; }
	int unitFactor() const { return mScales.at(mActiveScale); }

private:
	static const std::string ROOT_XML_TAG;
	static const std::string UNITS_FACTOR_XML_TAG;
	static const std::string SMALL_FACTOR_XML_TAG;
	static const std::string MEDIUM_FACTOR_XML_TAG;
	static const std::string LARGE_FACTOR_XML_TAG;
	static const std::string LAYOUT_XML_TAG;
	static const std::string LAYOUT_ROWS_ATTR;
	static const std::string LAYOUT_COLUMNS_ATTR;
	static const std::string LEGEND_XML_TAG;
	static const std::string ITEM_XML_TAG;
	static const std::string ITEM_KEY_ATTR;
	static const std::string ITEM_VALUE_ATTR;

	std::unordered_map<int, std::string> mLegend;
	std::unordered_map<Scale, int> mScales;
	Scale mActiveScale;
	std::vector<int> mLayout;
	int mRows;
	int mColumns;  // a.k.a. row-length
};

