#pragma once
#include "Rect.h"
#include "Texture.h"
#include "Drawable.h"

class Renderer;

class Sprite 
    : public Drawable {
public:
    Sprite(Texture& texture, Rect source);
    Sprite(const Sprite& other);
    ~Sprite();
    Sprite&         operator=(const Sprite& other);

    int             width() const           { return mSource.width(); }
    int             height() const          { return mSource.height(); }
    Rect            rect() const            { return mSource; }

    void            draw(const Renderer& renderer, const Rect& dest) override;

private:
    Texture&        mTexture;
    Rect            mSource;
};

