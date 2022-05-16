#pragma once

#include <iostream>
#include "gameObject.hpp"

enum class State : uint8_t {Idle1, Idle2, AboutToFire, Dead};
//params
static constexpr int animationFrequency = 2000;


class Enemy: public GameObject
{
public:
    explicit Enemy(uint16_t startX, uint16_t startY);
    explicit Enemy(uint16_t startX, uint16_t startY, uint16_t velX, uint16_t velY, uint8_t health);
    void gameTick(GameMaster *host, float deltaTime) override;

private:
    void loadTextures();
    void animate();
    void calculateMovement(float deltaTime) override;
    uint8_t m_health;

    int16_t m_velX, m_velY;
    uint16_t m_boundXlow, m_boundXhi;
    uint16_t m_boundYlow, m_boundYhi;

    std::array<sf::Texture, 2> textures;
    State state;

    friend class EnemyBuilder;
};

