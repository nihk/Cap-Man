#include "SpriteRepository.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "Surface.h"
#include "Texture.h"
#include "tinyxml2.h"

const std::string SpriteRepository::ROOT_XML_TAG = "sprites";
const std::string SpriteRepository::TEXTURE_XML_TAG = "texture";
const std::string SpriteRepository::NAME_ATTR = "name";
const std::string SpriteRepository::X_ATTR = "x";
const std::string SpriteRepository::Y_ATTR = "y";
const std::string SpriteRepository::WIDTH_ATTR = "w";
const std::string SpriteRepository::HEIGHT_ATTR = "h";

SpriteRepository::SpriteRepository()
	: mTexWidth(-1)
	, mTexHeight(-1) {
}

SpriteRepository::~SpriteRepository() {
}

bool SpriteRepository::initialize(Renderer& renderer, const std::string& spriteSheet, const std::string& spriteAtlas) {
	Surface surface;

	if (!surface.initialize(spriteSheet)) {
		std::cerr << "Error: Failed to load image from file: " << IMG_GetError() << std::endl;
		return false;
	}

	// Set the color key for transparency, if necessary
	//surface.setColorKey(Colors::MAGENTA);

	if (!mTexture.initialize(renderer, surface)) {
		std::cout << "Error: Failed to create texture: " << std::endl << SDL_GetError() << std::endl;
		return false;
	}

	mTexWidth = surface.width();
	mTexHeight = surface.height();

	if (!parseAtlas(spriteAtlas)) {
		return false;
	}

	return true;
}

Sprite SpriteRepository::findSprite(const std::string& spriteName) {
	return mAtlas.at(spriteName);
}

bool SpriteRepository::parseAtlas(const std::string& spriteAtlas) {
	tinyxml2::XMLDocument xmlDocument;
	if (xmlDocument.LoadFile(spriteAtlas.c_str()) != tinyxml2::XML_NO_ERROR) {
		xmlDocument.PrintError();
		return false;
	}

	tinyxml2::XMLElement* root = xmlDocument.FirstChildElement(ROOT_XML_TAG.data());
	if (!root) {
		xmlDocument.PrintError();
		std::cout << "Cannot find root element <"<< ROOT_XML_TAG << "> in " << spriteAtlas << std::endl;
		return false;
	}

	tinyxml2::XMLElement* texture = root->FirstChildElement(TEXTURE_XML_TAG.data());
	if (!texture) {
		xmlDocument.PrintError();
		std::cout << "Cannot find element <" << TEXTURE_XML_TAG << "> in " << spriteAtlas << std::endl;
		return false;
	}

	while (texture) {
		std::string name(texture->Attribute(NAME_ATTR.data()));
		int x = texture->IntAttribute(X_ATTR.data());
		int y = texture->IntAttribute(Y_ATTR.data());
		int w = texture->IntAttribute(WIDTH_ATTR.data());
		int h = texture->IntAttribute(HEIGHT_ATTR.data());
		Rect rect(x, y, w, h);
		Sprite sprite(mTexture, rect);

		mAtlas.insert_or_assign(name, sprite);
		texture = texture->NextSiblingElement(TEXTURE_XML_TAG.data());
	}

	return true;
}
