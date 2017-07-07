#include "ColorGraphicsComponent.h"
#include "Renderer.h"
#include "Rect.h"

ColorGraphicsComponent::ColorGraphicsComponent(Color color)
	: mColor(color) {
}

ColorGraphicsComponent::~ColorGraphicsComponent() {
}

void ColorGraphicsComponent::draw(const Renderer& renderer, const Rect& dest) {
	renderer.setDrawColor(mColor);
	renderer.fillRect(dest);
}
