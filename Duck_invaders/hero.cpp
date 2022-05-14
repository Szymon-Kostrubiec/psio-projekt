#include "hero.hpp"

Hero::Hero(uint16_t posX, uint16_t posY, uint16_t health) :
    GameObject(posX, posY), m_health(health)
{
    loadTextures();
    setPosition(posX, posY);
}

void Hero::gameTick([[maybe_unused]] GameMaster *host, float deltaTime)
{
   //todo: taking and receiving shots
    calculateMovement(deltaTime);
}

void Hero::calculateMovement(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        std::cout << "Space" << std::endl; //todo: firing
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_posY -= deltaTime * heroSpeed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_posY += deltaTime * heroSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_posX -= deltaTime * heroSpeed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_posX += deltaTime * heroSpeed;
    }
    setPosition(m_posX, m_posY);
}

void Hero::loadTextures()
{
    texture.loadFromFile("Textures/spaceship.png");
    setTexture(texture);
}
