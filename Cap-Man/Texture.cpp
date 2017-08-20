#include "Texture.h"
#include "Renderer.h"
#include "Surface.h"

Texture::Texture() 
    : mSdlTexture(nullptr) {
}

Texture::~Texture() {
    SDL_DestroyTexture(mSdlTexture);
}

bool Texture::initialize(Renderer& renderer, Surface& surface) {
    mSdlTexture = SDL_CreateTextureFromSurface(renderer.mutableData(), surface.mutableData());
    return mSdlTexture != nullptr;
}
