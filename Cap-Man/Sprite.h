#pragma once
#include <string>
#include "Rectangle.h"
#include "Texture.h"
#include "Drawable.h"

class Renderer;

class Sprite 
	: public Drawable {
public:
	Sprite(Texture texture, Rectangle source);
	virtual ~Sprite();

	int				width() const			{ return mSource.width(); }
	int				height() const			{ return mSource.height(); }
	Rectangle		getRectangle() const	{ return mSource; }
	Texture			getTexture() const		{ return mTexture; }

	static Texture	loadTexture(const std::string& filePath, Renderer& renderer, int& w /* out */, int& h /* out */);
	void			draw(Renderer& renderer, const Rectangle& dest) override;

private:
	Texture			mTexture;
	Rectangle		mSource;
};

