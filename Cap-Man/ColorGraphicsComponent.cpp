#include "ColorGraphicsComponent.h"
#include "Renderer.h"
#include "Rect.h"

ColorGraphicsComponent::ColorGraphicsComponent(Color color)
	: mColor(color) {
}

ColorGraphicsComponent::~ColorGraphicsComponent() {
}

void ColorGraphicsComponent::draw(Renderer& renderer, const Rect& dest) {
	SDL_SetRenderDrawColor(renderer.mutableData(), mColor.r(), mColor.g(), mColor.b(), mColor.a());
	SDL_RenderFillRect(renderer.mutableData(), dest.data());
}
