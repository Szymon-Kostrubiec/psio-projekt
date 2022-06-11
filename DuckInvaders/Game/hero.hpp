#pragma once

#include "gameObject.hpp"
#include "gameengine.hpp"
#include "projectile.hpp"
#include "utility.hpp"
#include "managers.h"

enum class Direction{Left, Up, Right};

class Hero: public GameObject
{
public:
    Hero(GameEngine * host, uint16_t posX, uint16_t posY, uint16_t health, std::string const &playerFileName);
    void gameTick(float deltaTime) override;
    int16_t health() const;
    void decreaseHealth(int16_t amount);

private:
    void animate();
    void calculateMovement(float);
    void fire();
    uint32_t lastFired;
    static constexpr auto firingCooldown = 500;
    int16_t m_health;
    sf::Texture m_texture;
    static const std::array<sf::IntRect, 3> m_texRects;
    static constexpr uint16_t heroSpeed{200};
    ProjectileLevel m_currentProjectileLevel;
};

