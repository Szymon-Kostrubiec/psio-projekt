#include "texturemanager.h"

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
