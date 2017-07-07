#include "Renderer.h"
#include <SDL.h>
#include "Window.h"
#include "Color.h"
#include "Rect.h"
#include "Texture.h"

Renderer::Renderer() 
	: mSdlRenderer(nullptr) {
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(mSdlRenderer);
}

bool Renderer::initialize(const Window& window) {
	mSdlRenderer = SDL_CreateRenderer(window.mSdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return mSdlRenderer != nullptr;
}

void Renderer::setDrawColor(const Color& color) const {
	SDL_SetRenderDrawColor(mSdlRenderer, color.r(), color.g(), color.b(), color.a());
}

void Renderer::fillRect(const Rect& rect) const {
	SDL_RenderFillRect(mSdlRenderer, rect.data());
}

void Renderer::copyTexture(Texture& texture, const Rect& source, const Rect& dest) const {
	SDL_RenderCopy(mSdlRenderer, texture.mutableData(), source.data(), dest.data());
}

void Renderer::clear() const {
	SDL_RenderClear(mSdlRenderer);
}

void Renderer::present() const {
	SDL_RenderPresent(mSdlRenderer);
}
