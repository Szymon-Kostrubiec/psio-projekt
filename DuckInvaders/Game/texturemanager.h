#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
    static TextureManager& get() {
        static TextureManager obj;
        return obj;
    }

    sf::Texture& getTex(std::string const &textureName);

private:

    std::map<std::string, sf::Texture> textureMap;

    TextureManager();
    TextureManager(TextureManager&) = delete;
    TextureManager(TextureManager&&) = delete;
};

