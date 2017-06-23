#include <iostream>
#include "Map.h"
#include "Globals.h"
#include "tinyxml2.h"

const std::string Map::ROOT_XML_TAG = "map";
const std::string Map::UNITS_FACTOR_XML_TAG = "unitsFactor";
const std::string Map::SMALL_FACTOR_XML_TAG = "small";
const std::string Map::MEDIUM_FACTOR_XML_TAG = "medium";
const std::string Map::LARGE_FACTOR_XML_TAG = "large";
const std::string Map::LAYOUT_XML_TAG = "layout";
const std::string Map::LAYOUT_ROWS_ATTR = "rows";
const std::string Map::LAYOUT_COLUMNS_ATTR = "columns";
const std::string Map::LEGEND_XML_TAG = "legend";
const std::string Map::ITEM_XML_TAG = "item";
const std::string Map::ITEM_KEY_ATTR = "key";
const std::string Map::ITEM_VALUE_ATTR = "value";

Map::Map() 
	: mActiveScale(Scale::SMALL)
	, mRows(-1)
	, mColumns(-1) {
}

Map::~Map() {
}

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

	tinyxml2::XMLElement* unitsFactor = root->FirstChildElement(UNITS_FACTOR_XML_TAG.data());
	if (!unitsFactor) {
		xmlDocument.PrintError();
		std::cout << "Cannot find element <" << UNITS_FACTOR_XML_TAG << "> in " << fileName << std::endl;
		return false;
	}

	tinyxml2::XMLElement* smallFactor = unitsFactor->FirstChildElement(SMALL_FACTOR_XML_TAG.data());
	if (!unitsFactor) {
		xmlDocument.PrintError();
		std::cout << "Cannot find element <" << SMALL_FACTOR_XML_TAG << "> in " << fileName << std::endl;
		return false;
	}

	tinyxml2::XMLElement* mediumFactor = smallFactor->NextSiblingElement(MEDIUM_FACTOR_XML_TAG.data());
	if (!unitsFactor) {
		xmlDocument.PrintError();
		std::cout << "Cannot find element <" << MEDIUM_FACTOR_XML_TAG << "> in " << fileName << std::endl;
		return false;
	}

	tinyxml2::XMLElement* largeFactor = mediumFactor->NextSiblingElement(LARGE_FACTOR_XML_TAG.data());
	if (!unitsFactor) {
		xmlDocument.PrintError();
		std::cout << "Cannot find element <" << LARGE_FACTOR_XML_TAG << "> in " << fileName << std::endl;
		return false;
	}

	// Parse the scaling factor sizes
	int small, medium, large;
	smallFactor->QueryIntText(&small);
	mediumFactor->QueryIntText(&medium);
	largeFactor->QueryIntText(&large);
	mScales.insert_or_assign(Scale::SMALL, small);
	mScales.insert_or_assign(Scale::MEDIUM, medium);
	mScales.insert_or_assign(Scale::LARGE, large);

	tinyxml2::XMLElement* layout = unitsFactor->NextSiblingElement(LAYOUT_XML_TAG.data());
	if (!layout) {
		xmlDocument.PrintError();
		std::cout << "Cannot find element <" << LAYOUT_XML_TAG << "> in " << fileName << std::endl;
		return false;
	}
	
	// Parse the map layout
	mRows = layout->IntAttribute(LAYOUT_ROWS_ATTR.data());
	mColumns = layout->IntAttribute(LAYOUT_COLUMNS_ATTR.data());
	std::string map = layout->GetText();
	for (auto& c : map) {
		// Converts char numbers to their int number equivalents,
		// e.g. '0' -> 0 or '1' -> 1
		mLayout.push_back(c - '0');
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
		int key = item->IntAttribute(ITEM_KEY_ATTR.data());
		std::string value = item->Attribute(ITEM_VALUE_ATTR.data());
		mLegend.insert_or_assign(key, value);
		item = item->NextSiblingElement(ITEM_XML_TAG.data());
	}

	return true;
}

int Map::getMapElement(int x, int y) {
	int index = x + y * mRows;
	return mLayout.at(index);
}

int Map::indexOf(int element) {
	// TODO
	return -1;
}

int Map::width() const {
	return mScales.at(mActiveScale) * mColumns;
}

int Map::height() const {
	return mScales.at(mActiveScale) * mRows;
}