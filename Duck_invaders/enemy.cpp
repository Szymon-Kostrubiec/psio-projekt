#include "enemy.hpp"

Enemy::Enemy(uint16_t startX, uint16_t startY) :
    GameObject(startX, startY)
{
    loadTextures();
}

Enemy::Enemy(uint16_t startX, uint16_t startY, uint16_t velX, uint16_t velY, uint8_t health) :
    GameObject(startX, startY), m_velX(velX), m_velY(velY), m_health(health)
{
    loadTextures();
}

void Enemy::gameTick([[maybe_unused]] GameMaster *host, float deltaTime)
{
    calculateMovement(deltaTime);
    animate();
}

void Enemy::loadTextures()
{
    if (not textures.at(0).loadFromFile("Textures/Idle 001.png"))
        std::cerr << "Could not load texture 1" << std::endl;
    if (not textures.at(1).loadFromFile("Textures/Idle 002.png"))
        std::cerr << "Could not load texture 2" << std::endl;

    setTexture(textures.at(1));
}

void Enemy::animate()
{
    static uint8_t animationClock{1};

    if (animationClock % animationFrequency == 0)
    {
        if (state == State::Idle1)
            state = State::Idle2;
        else
            state = State::Idle1;

        setTexture(textures.at(static_cast<uint8_t>(state)));
    }
    animationClock++;
}

void Enemy::calculateMovement(float deltaTime)
{
    m_posX += deltaTime * m_velX;
    m_posY += deltaTime * m_velY;
    setPosition(m_posX, m_posY);
}
