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
    void draw(const Renderer& renderer, const Rect& dest) override;

private:
    Color mColor;
};

