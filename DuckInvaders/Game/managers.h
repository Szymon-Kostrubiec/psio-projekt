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
public:
    TextureManager(TextureManager&) = delete;
    TextureManager(TextureManager&&) = delete;
};

class FontManager {
public:
    static FontManager& get() {
        static FontManager obj;
        return obj;
    }
    sf::Font& getFont(std::string const &fileName);

private:

    std::map<std::string, sf::Font> fontMap;

    FontManager();
public:
    FontManager(FontManager&) = delete;
    FontManager(FontManager&&) = delete;
};
