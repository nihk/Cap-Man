#pragma once

class Renderer;
class Rect;

class Drawable {
public:
    virtual ~Drawable() = default;

    virtual void draw(const Renderer& renderer, const Rect& dest) = 0;
};
