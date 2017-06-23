#pragma once

#include "Component.h"
#include "Renderer.h"
#include "Rectangle.h"
#include "Drawable.h"

class GraphicsComponent
	: public Component<GraphicsComponent>
	, public Drawable {
public:
	GraphicsComponent() = default;
	~GraphicsComponent() = default;

	void draw(Renderer& renderer, const Rectangle& dest) override { /* Stub */ }
};

