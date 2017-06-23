#pragma once
#include "GraphicsComponent.h"
#include "Animation.h"

class SpriteGraphicsComponent
	: public GraphicsComponent {
public:
	// TODO: unique_ptr instead?
	SpriteGraphicsComponent(Animation animation);
	~SpriteGraphicsComponent();

	void draw(Renderer& renderer, const Rectangle& dest) override;

private:
	Animation mAnimation;
};

