#include "Renderer.h"
#include <SDL.h>
#include "Window.h"
#include "Color.h"

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

void Renderer::clear() const {
	SDL_RenderClear(mSdlRenderer);
}

void Renderer::present() const {
	SDL_RenderPresent(mSdlRenderer);
}
