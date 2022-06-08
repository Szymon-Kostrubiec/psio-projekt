#include "managers.h"

sf::Texture &TextureManager::getTex(const std::string &textureName)
{
    if (not textureMap.count(textureName)) {
        textureMap[textureName]; //implicit creation
        textureMap.at(textureName).loadFromFile(textureName);
    }
    return textureMap.at(textureName);
}

TextureManager::TextureManager()
{

}

sf::Font &FontManager::getFont(const std::string &fileName)
{
    if (not fontMap.count(fileName)) {
        fontMap[fileName]; //implicit creation
        fontMap.at(fileName).loadFromFile(fileName);
    }
    return fontMap.at(fileName);
}

FontManager::FontManager()
{

}
