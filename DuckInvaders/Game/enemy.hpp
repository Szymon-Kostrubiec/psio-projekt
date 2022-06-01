#pragma once

#include <iostream>
#include <memory>
#include "gameObject.hpp"
#include "movement.hpp"

enum class State : uint8_t {Idle1, Idle2, AboutToFire, Dead};
//params
static constexpr int animationFrequency = 2000;


class Enemy: public GameObject
{
public:
    explicit Enemy(GameEngine * host, uint16_t startX, uint16_t startY);
    void gameTick(float deltaTime) override;

private:
    void loadTextures();
    void animate();
    void spawnProjectile();
    const uint32_t projectileTimeout;
    static constexpr auto projectileChance = 0.3;
    uint32_t lastProjectileFired;
    uint8_t m_health;

    std::array<sf::Texture, 2> textures;
    sf::Texture textureDead;
    State state;

    std::unique_ptr<MovementCalc> movement;
    int16_t m_vel;

    friend class EnemyBuilder;
};

