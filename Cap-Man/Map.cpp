#include <iostream>
#include "Map.h"
#include "Constants.h"
#include "tinyxml2.h"

const std::string Map::ROOT_XML_TAG = "map";
const std::string Map::UNIT_PIXEL_SIZE_XML_TAG = "unitPixelSize";
const std::string Map::UNIT_SCALE_XML_TAG = "unitScale";
const std::string Map::SMALL_SCALE_XML_TAG = "small";
const std::string Map::LARGE_SCALE_XML_TAG = "large";
const std::string Map::LAYOUT_XML_TAG = "layout";
const std::string Map::LAYOUT_ROWS_ATTR = "rows";
const std::string Map::LAYOUT_COLUMNS_ATTR = "columns";
const std::string Map::LEGEND_XML_TAG = "legend";
const std::string Map::ITEM_XML_TAG = "item";
const std::string Map::ITEM_KEY_ATTR = "key";
const std::string Map::ITEM_VALUE_ATTR = "value";

Map::Map()
    : mUnitPixelSize(-1)
<<<<<<< HEAD
    , mActiveScale(Scale::LARGE)
=======
    , mActiveScale(Scale::SMALL)
>>>>>>> Tabs --> spaces
    , mRows(-1)
    , mColumns(-1) {
}

Map::~Map() {
}

// TODO: This classes calculation logic needs to be less dumbified
// TODO: Make a map of <Point, int>?

bool Map::initialize(std::string fileName) {
    tinyxml2::XMLDocument xmlDocument;
    if (xmlDocument.LoadFile(fileName.data()) != tinyxml2::XML_NO_ERROR) {
        xmlDocument.PrintError();
        return false;
    }

    tinyxml2::XMLElement* root = xmlDocument.FirstChildElement(ROOT_XML_TAG.data());
    if (!root) {
        xmlDocument.PrintError();
        std::cout << "Cannot find root element <" << ROOT_XML_TAG << "> in " << fileName << std::endl;
        return false;
    }

    tinyxml2::XMLElement* unitPixelSize = root->FirstChildElement(UNIT_PIXEL_SIZE_XML_TAG.data());
    if (!unitPixelSize) {
        xmlDocument.PrintError();
        std::cout << "Cannot find element <" << UNIT_PIXEL_SIZE_XML_TAG << "> in " << fileName << std::endl;
        return false;
    }

    tinyxml2::XMLElement* unitScale = unitPixelSize->NextSiblingElement(UNIT_SCALE_XML_TAG.data());
    if (!unitScale) {
        xmlDocument.PrintError();
        std::cout << "Cannot find element <" << UNIT_SCALE_XML_TAG << "> in " << fileName << std::endl;
        return false;
    }

    tinyxml2::XMLElement* smallFactor = unitScale->FirstChildElement(SMALL_SCALE_XML_TAG.data());
    if (!smallFactor) {
        xmlDocument.PrintError();
        std::cout << "Cannot find element <" << SMALL_SCALE_XML_TAG << "> in " << fileName << std::endl;
        return false;
    }

    tinyxml2::XMLElement* largeFactor = smallFactor->NextSiblingElement(LARGE_SCALE_XML_TAG.data());
    if (!largeFactor) {
        xmlDocument.PrintError();
        std::cout << "Cannot find element <" << LARGE_SCALE_XML_TAG << "> in " << fileName << std::endl;
        return false;
    }

    // Parse the scaling factor sizes
    int small, large;
    unitPixelSize->QueryIntText(&mUnitPixelSize);
    smallFactor->QueryIntText(&small);
    largeFactor->QueryIntText(&large);
    mScales.insert_or_assign(Scale::SMALL, small);
    mScales.insert_or_assign(Scale::LARGE, large);

    tinyxml2::XMLElement* layout = unitScale->NextSiblingElement(LAYOUT_XML_TAG.data());
    if (!layout) {
        xmlDocument.PrintError();
        std::cout << "Cannot find element <" << LAYOUT_XML_TAG << "> in " << fileName << std::endl;
        return false;
    }
    
    // Parse the map layout
    mRows = layout->IntAttribute(LAYOUT_ROWS_ATTR.data());
    mColumns = layout->IntAttribute(LAYOUT_COLUMNS_ATTR.data());
    std::string map = layout->GetText();
    int layoutIndex = 0;
    for (auto& c : map) {
        // Converts char numbers to their int number equivalents,
        // e.g. '0' -> 0 or '1' -> 1
        int i = c - '0';

        mLayout.push_back(i);

        if (i != MapLayoutElements::WALL) {
            mNavigableIndices.push_back(layoutIndex);
        }

        ++layoutIndex;
    }

    tinyxml2::XMLElement* legend = layout->NextSiblingElement(LEGEND_XML_TAG.data());
    if (!legend) {
        xmlDocument.PrintError();
        std::cout << "Cannot find element <" << LEGEND_XML_TAG << "> in " << fileName << std::endl;
        return false;
    }

    tinyxml2::XMLElement* item = legend->FirstChildElement(ITEM_XML_TAG.data());
    if (!item) {
        xmlDocument.PrintError();
        std::cout << "Cannot find element <" << ITEM_XML_TAG << "> in " << fileName << std::endl;
        return false;
    }

    // Parse the items
    while (item != nullptr) {
        std::string key = item->Attribute(ITEM_KEY_ATTR.data());
        int value = item->IntAttribute(ITEM_VALUE_ATTR.data());
        mLegend.insert_or_assign(key, value);
        item = item->NextSiblingElement(ITEM_XML_TAG.data());
    }

    return true;
}

// Assumes unit length scaling
int Map::mapElement(int x, int y) const {
    int index = x + y * mColumns;
    return mLayout.at(index);
}

int Map::mapElement(const Point& point) const {
    return mapElement(point.x(), point.y());
}

Point Map::startLocation(StartLocation startLocation) const {
    // TODO
    return Point();
}

int Map::mapLocation(Point location, bool scaleUtoP) const {
    if (scaleUtoP) {
        scaleUnitsToPixels(location);
    }

    return location.x() + location.y() * mColumns;
}

// TODO: Refactor this to be less stupid
Point Map::mapLocation(int layoutIndex, bool scaleUtoP) const {
    int x = layoutIndex % mColumns;
    int y = layoutIndex / mColumns;

    if (scaleUtoP) {
        scaleUnitsToPixels(x, y);
    }

    return Point(x, y);
}

int Map::indexOf(int element) {
    for (size_t i = 0; i < mLayout.size(); ++i) {
        if (mLayout.at(i) == element) {
            return i;
        }
    }

    return -1;
}

int Map::widthPixels() const {
    return unitPixels(mColumns);
}

int Map::heightPixels() const {
    return unitPixels(mRows);
}

int Map::singleUnitPixels() const {
    return unitPixels(1);
}

int Map::unitPixels(int numUnits) const {
    return numUnits * mScales.at(mActiveScale) * mUnitPixelSize;
}

int Map::neighbourElement(Point location, bool scalePtoU, Directions::Direction direction) const {
    if (scalePtoU) {
        scalePixelsToUnits(location);
    }

    switch (direction) {
        case Directions::UP: {
            if (location.y() == 0) {
                return MapLayoutElements::EDGE;
            }
            location.setY(location.y() - 1);
            break;
        }
        case Directions::RIGHT: {
            if (location.x() == mColumns - 1) {
                return MapLayoutElements::EDGE;
            }
            location.setX(location.x() + 1);
            break;
        }
        case Directions::DOWN: {
            if (location.y() == mRows - 1) {
                return MapLayoutElements::EDGE;
            }
            location.setY(location.y() + 1);
            break;
        }
        case Directions::LEFT: {
            if (location.x() == 0) {
                return MapLayoutElements::EDGE;
            }
            location.setX(location.x() - 1);
            break;
        }
        default: {
            return MapLayoutElements::INVALID;
        }
    }

    return mapElement(location.x(), location.y());
}

void Map::scaleUnitsToPixels(int& x, int& y) const {
    x *= singleUnitPixels();
    y *= singleUnitPixels();
}

void Map::scaleUnitsToPixels(Point& point) const {
    point.setX(point.x() * singleUnitPixels());
    point.setY(point.y() * singleUnitPixels());
}

void Map::scalePixelsToUnits(int& x, int& y) const {
    x /= singleUnitPixels();
    y /= singleUnitPixels();
}

void Map::scalePixelsToUnits(Point& point) const {
    point.setX(point.x() / singleUnitPixels());
    point.setY(point.y() / singleUnitPixels());
}
