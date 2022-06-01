#include "enemy.hpp"

namespace Game{
uint32_t globalTime;
}

Enemy::Enemy(GameEngine *host, uint16_t startX, uint16_t startY) :
    GameObject(startX, startY), projectileTimeout(1000), lastProjectileFired(0)
{
    loadTextures();
}

void Enemy::gameTick(float deltaTime)
{
    if (state not_eq State::Dead) {
        setPosition(movement->getNextPosition(deltaTime * m_vel));
    }
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
    if (state not_eq State::Dead) {
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
    else {
        setTexture(textureDead);
    }
}

void Enemy::spawnProjectile()
{
    if (lastProjectileFired + projectileTimeout < Game::globalTime) {

        lastProjectileFired = Game::globalTime;

        if (randomDouble(1.0) < projectileChance) {
            auto projectile =
        }

    }
}
