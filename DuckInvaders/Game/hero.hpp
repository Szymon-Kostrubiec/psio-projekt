#pragma once

#include "gameObject.hpp"
#include "gameengine.hpp"
#include "projectile.hpp"
#include "utility.hpp"
#include "texturemanager.h"

class Hero: public GameObject
{
public:
    Hero(GameEngine * host, uint16_t posX, uint16_t posY, uint16_t health, std::string const &playerFileName);
    void gameTick(float deltaTime) override;
    int16_t health() const;
    void decreaseHealth(uint16_t amount);

private:
    void calculateShots(GameEngine * host);
    int16_t m_health;
    sf::Texture m_texture;
    static constexpr uint16_t heroSpeed{200};
    ProjectileLevel m_currentProjectileLevel;
    uint32_t m_firingCooldown;
};

