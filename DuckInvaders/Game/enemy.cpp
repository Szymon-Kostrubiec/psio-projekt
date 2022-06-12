#include "enemy.hpp"

namespace Game{
uint32_t globalTime;
}

Enemy::Enemy(GameEngine *host, uint16_t startX, uint16_t startY) :
    GameObject(host, startX, startY), projectileTimeout(1000), lastProjectileFired(0),
    m_health(30), movement(getRandomMovement())
{
    loadTextures();
    textureDead.loadFromFile("Textures/deadduck.png");
}

Enemy::~Enemy()
{
    delete movement;
}

void Enemy::gameTick([[maybe_unused]]float deltaTime)
{
    if (m_posX < 0 or m_posX > windowX or m_posY < 0 or m_posY > windowY) {
        die();
    }
    if (not dead()) {
        setPosition(movement->getNextPosition(deltaTime));
        if (m_health <= 0) {
            die();
            return;
        }
    }
    else {
        if (Game::globalTime > timeOfDeath + 500 and dead()) {
            expired = true;
        }
    }
    animate();
    spawnProjectile();
}

void Enemy::die()
{
    state = State::Dead;
    timeOfDeath = Game::globalTime;
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
    if (dead())
        return;

    if (lastProjectileFired + projectileTimeout < Game::globalTime) {

        lastProjectileFired = Game::globalTime;

        if (randomDouble(1.0) < projectileChance) {
            auto projectile = std::make_shared<EnemyProjectile>(host, m_posX, m_posY, 0, 400,
                                                                (randomInt(10) < 7) ? Type::Damage : Type::Health);
            host->addObject(projectile);
        }

    }
}
