#pragma once

#include <unordered_map>
#include <string>

#include "Texture.h"
#include "Sprite.h"

namespace tinyxml2 {
    class XMLElement;
}

class Renderer;

class SpriteRepository {
public:
    SpriteRepository();
    ~SpriteRepository();

    bool initialize(Renderer& renderer, const std::string& spriteSheet, const std::string& spriteAtlas);
    Sprite findSprite(const std::string& spriteName);

private:
    static const std::string ROOT_XML_TAG;
    static const std::string TEXTURE_XML_TAG;
    static const std::string NAME_ATTR;
    static const std::string X_ATTR;
    static const std::string Y_ATTR;
    static const std::string WIDTH_ATTR;
    static const std::string HEIGHT_ATTR;

    bool parseAtlas(const std::string& spriteAtlas);

    std::unordered_map<std::string, Sprite> mAtlas;
    Texture mTexture;
    int mTexWidth;
    int mTexHeight;
};

