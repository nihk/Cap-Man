#pragma once

class Renderer;
class Rect;

class Drawable {
public:
	virtual ~Drawable() = default;

	virtual void draw(Renderer& renderer, const Rect& dest) = 0;
};
