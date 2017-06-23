#pragma once

class Renderer;
class Rectangle;

class Drawable {
public:
	virtual ~Drawable() = default;

	virtual void draw(Renderer& renderer, const Rectangle& dest) = 0;
};
