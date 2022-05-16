#include "projectile.hpp"

Projectile::Projectile(uint16_t posX, uint16_t posY, uint16_t velX, uint16_t velY, ProjectileLevel level) :
    GameObject(posX, posY), m_velX(velX), m_velY(velY)
{
    m_damagePotential = damagePotentials.at(static_cast<uint8_t>(level));
    m_texture.loadFromFile("Textures/" + projectileFileNames.at(static_cast<uint8_t>(level)));
    setTexture(m_texture);
    setRotation(-90);
}

void Projectile::gameTick(GameMaster *host, float deltaTime)
{
    calculateMovement(deltaTime);

//    if (m_posY < -50)
//        host->removeMe(this);
}

void Projectile::calculateMovement(float deltaTime)
{
    m_posX += deltaTime * m_velX;
    m_posY += deltaTime * m_velY;

    setPosition(m_posX, m_posY);
}
