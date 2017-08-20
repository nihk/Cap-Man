#include "Sprite.h"
#include "Renderer.h"

Sprite::Sprite(Texture& texture, Rect source) 
    : mTexture(texture) 
    , mSource(source) {
}

Sprite::Sprite(const Sprite& other) 
    : mTexture(other.mTexture)
    , mSource(other.mSource) {
}

Sprite::~Sprite() {
}

Sprite& Sprite::operator=(const Sprite& other) {
    mTexture = other.mTexture;
    mSource = other.mSource;
    return *this;
}

void Sprite::draw(const Renderer& renderer, const Rect& dest) {
    renderer.copyTexture(mTexture, mSource, dest);
}
