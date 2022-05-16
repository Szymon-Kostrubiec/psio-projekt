#include "hero.hpp"

Hero::Hero(uint16_t posX, uint16_t posY, uint16_t health) :
    GameObject(posX, posY), m_health(health), m_currentProjectileLevel(ProjectileLevel::Level1)
{
    loadTextures();
    setPosition(posX, posY);
}

void Hero::gameTick([[maybe_unused]] GameMaster *host, float deltaTime)
{
   //todo: taking and receiving shots
    calculateMovement(deltaTime);
    calculateShots(host);
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

void Hero::calculateShots(GameMaster *host)
{
    if (not sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        return;
    }
//    if (m_firingCooldown < Game::globalTime) {
//        auto projectile = std::make_shared<Projectile>(m_posX, m_posY, 0, -250, m_currentProjectileLevel);
//        host->addObject(projectile);
//        m_firingCooldown = Game::globalTime + 1000;
//    }
}

void Hero::loadTextures()
{
    m_texture.loadFromFile("Textures/spaceship.png");
    setTexture(m_texture);
}
