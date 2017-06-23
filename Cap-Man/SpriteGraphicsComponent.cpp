#include "SpriteGraphicsComponent.h"
#include "Renderer.h"

SpriteGraphicsComponent::SpriteGraphicsComponent(Animation animation)
	: mAnimation(animation) {
}

SpriteGraphicsComponent::~SpriteGraphicsComponent() {
}

void SpriteGraphicsComponent::draw(Renderer& renderer, const Rectangle& dest) {
	mAnimation.draw(renderer, dest);
}

