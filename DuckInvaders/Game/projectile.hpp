#pragma once

#include "gameObject.hpp"
#include "gameengine.hpp"
#include "utility.hpp"

static const std::array<std::string, 4> projectileFileNames{"Projectile1.png", "Projectile2.png", "Projectile3.png",
                                                           "Projectile4.png"};
static const std::array<uint8_t, 4> damagePotentials{30, 50, 70, 150};

enum class Type : uint8_t {Damage, Health};

class Projectile : public GameObject
{
public:
    Projectile(GameEngine * host, uint16_t posX, uint16_t posY, uint16_t velX, uint16_t velY, ProjectileLevel level,
               Type type = Type::Damage);
    void gameTick(float deltaTime) override;
    uint8_t damagePotential() const {return m_damagePotential;}
private:
    void calculateMovement(float);
    uint8_t m_damagePotential;
    int16_t m_velX, m_velY;
    sf::Texture m_texture;
};
