#include "ColorGraphicsComponent.h"
#include "Renderer.h"
#include "Rectangle.h"

ColorGraphicsComponent::ColorGraphicsComponent(Color color)
	: mColor(color) {
}

ColorGraphicsComponent::~ColorGraphicsComponent() {
}

void ColorGraphicsComponent::draw(Renderer& renderer, const Rectangle& dest) {
	SDL_SetRenderDrawColor(renderer.mutableData(), mColor.r(), mColor.g(), mColor.b(), mColor.a());
	SDL_RenderFillRect(renderer.mutableData(), dest.data());
}
