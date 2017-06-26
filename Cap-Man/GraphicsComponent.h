#pragma once

#include "Component.h"
#include "Renderer.h"
#include "Rect.h"
#include "Drawable.h"

class GraphicsComponent
	: public Component<GraphicsComponent>
	, public Drawable {
public:
	GraphicsComponent() = default;
	~GraphicsComponent() = default;

	virtual void update(float delta, int state) { /* stub */}
	void draw(Renderer& renderer, const Rect& dest) override { /* Stub */ }
};

