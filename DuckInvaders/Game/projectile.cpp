#include "projectile.hpp"

Projectile::Projectile(GameEngine * host, uint16_t posX, uint16_t posY, uint16_t velX, uint16_t velY, ProjectileLevel level) :
    GameObject(host, posX, posY), m_velX(velX), m_velY(velY)
{
    m_damagePotential = damagePotentials.at(static_cast<uint8_t>(level));
    m_texture.loadFromFile("Textures/" + projectileFileNames.at(static_cast<uint8_t>(level)));
    setTexture(m_texture);
    setRotation(-90);
}

void Projectile::gameTick(float deltaTime)
{
    calculateMovement(deltaTime);

    if (m_posX < -50 or m_posX > windowX + 50 or m_posY < -50 or m_posY > windowY + 50) {
        expired = true;
    }
}

void Projectile::calculateMovement(float deltaTime)
{
    m_posX += deltaTime * m_velX;
    m_posY += deltaTime * m_velY;

    setPosition(m_posX, m_posY);
}

EnemyProjectile::EnemyProjectile(GameEngine *host, uint16_t posX, uint16_t posY, uint16_t velX, uint16_t velY, Type type) :
    Projectile(host, posX, posY, velX, velY, static_cast<ProjectileLevel>(0))
{
    if (type == Type::Damage) {
        m_texture.loadFromFile("Textures/Egg.png");
        m_damagePotential = 50;
    }
    else if (type == Type::Health) {
        m_damagePotential = -50;
        m_texture.loadFromFile("Textures/Heart.png");
        setScale(0.5f, 0.5f);
    }
}
