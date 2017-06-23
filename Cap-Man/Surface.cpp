#include <SDL_image.h>
#include "Surface.h"
#include "Color.h"

Surface::Surface()
	: mSdlSurface(nullptr) {
}

bool Surface::initialize(const std::string& filePath) {
	mSdlSurface = IMG_Load(filePath.data());
	return mSdlSurface != nullptr;
}

void Surface::setColorKey(const Color& color) const {
	SDL_SetColorKey(mSdlSurface, SDL_TRUE, SDL_MapRGB(mSdlSurface->format, color.r(), color.g(), color.b()));
}

int Surface::width() const {
	return mSdlSurface ? mSdlSurface->w : -1;
}

int Surface::height() const {
	return mSdlSurface ? mSdlSurface->h : -1;
}

Surface::~Surface() {
	SDL_FreeSurface(mSdlSurface);
}
