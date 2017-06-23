#pragma once

#include "GraphicsComponent.h"
#include "Color.h"

class ColorGraphicsComponent
	: public GraphicsComponent {
public:
	ColorGraphicsComponent(Color color);
	~ColorGraphicsComponent();

	Color color() const { return mColor; }
	void setColor(Color color) { mColor = color; }
	void draw(Renderer& renderer, const Rectangle& dest) override;

private:
	Color mColor;
};

