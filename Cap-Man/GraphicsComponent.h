#pragma once

#include "Component.h"
#include "Renderer.h"
#include "Rect.h"
#include "Drawable.h"

class GraphicsComponent
	: public Component<GraphicsComponent>
	, public Drawable {
public:
	GraphicsComponent();
	GraphicsComponent(bool shouldDraw);
	~GraphicsComponent();

	virtual void update(float delta, int state) { /* do nothing */}
	void draw(const Renderer& renderer, const Rect& dest) override { /* do nothing */ }
	bool shouldDraw() const { return mShouldDraw; }
	void setShouldDraw(bool shouldDraw) { mShouldDraw = shouldDraw; }

private:
	bool mShouldDraw;
};

