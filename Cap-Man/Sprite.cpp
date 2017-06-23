#include <iostream>
#include <SDL_image.h>
#include "Sprite.h"
#include "Surface.h"
#include "Renderer.h"

Sprite::Sprite(Texture texture, Rectangle source) 
	: mTexture(texture) 
	, mSource(source) {
}

Sprite::~Sprite() {
}

// TODO: Move this out of this class? Only SpriteAtlas will use it
Texture Sprite::loadTexture(const std::string& filePath, Renderer& renderer, int& w, int& h) {
	Texture texture;
	Surface surface;

	if (!surface.initialize(filePath)) {
		std::cerr << "Error: Failed to load image from file: " << IMG_GetError() << std::endl;
	}

	// Set the color key for transparency, if necessary
	//surface.setColorKey(Colors::MAGENTA);

	if (!texture.initialize(renderer, surface)) {
		std::cout << "Error: Failed to create texture: " << std::endl << SDL_GetError() << std::endl;
	}

	w = surface.width();
	h = surface.height();

	// FIXME: This value type return will call the destructor to destroy its internal pointer!
	return texture;
}

void Sprite::draw(Renderer& renderer, const Rectangle& dest) {
	SDL_RenderCopy(renderer.mutableData(), mTexture.mutableData(), mSource.data(), dest.data());
}
