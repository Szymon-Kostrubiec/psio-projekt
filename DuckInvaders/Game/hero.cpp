#include "hero.hpp"

Hero::Hero(GameEngine * host, uint16_t posX, uint16_t posY, uint16_t health, const std::string &playerFileName) :
    GameObject(host, posX, posY), m_health(health), m_currentProjectileLevel(ProjectileLevel::Level1)
{
    m_texture.loadFromFile(playerFileName);
}

void Hero::gameTick(float deltaTime)
{
   //todo: taking and receiving shots
    calculateMovement(deltaTime);
}

void Hero::calculateMovement(float deltaTime)
{
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

int16_t Hero::health() const
{
    return m_health;
}

void Hero::decreaseHealth(uint16_t amount)
{
    m_health -= amount;
}

