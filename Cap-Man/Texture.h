#pragma once
#include <SDL.h>
#include "Wrapper.h"

class Renderer;
class Surface;

class Texture 
    : public Wrapper<SDL_Texture> {
public:
    Texture();
    ~Texture();

    bool initialize(Renderer& renderer, Surface& surface);
    const SDL_Texture* data() const override { return mSdlTexture; }
    SDL_Texture* mutableData() override { return mSdlTexture; }

private:
    SDL_Texture* mSdlTexture;
};

