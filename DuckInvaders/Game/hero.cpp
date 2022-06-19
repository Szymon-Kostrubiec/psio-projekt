#include "hero.hpp"

namespace Game {
extern uint32_t globalTime;
}

const std::array<sf::IntRect, 3> Hero::m_texRects{
    sf::IntRect(0, 0, 8, 8), sf::IntRect(8, 0, 8, 8), sf::IntRect(16, 0, 8, 8)};

Hero::Hero(GameEngine *host, uint16_t posX, uint16_t posY, uint16_t health,
           const std::string &playerFileName)
    : GameObject(host, posX, posY), lastFired(0), m_health(health),
      m_currentProjectileLevel(ProjectileLevel::Level1) {
  m_texture.loadFromFile(playerFileName);
  setTexture(m_texture);
  setScale(10, 10);
  firingSoundBuffer.loadFromFile("Sounds/pop.wav");
  firingSound.setBuffer(firingSoundBuffer);
}

void Hero::gameTick(float deltaTime) {
  // todo: taking and receiving shots
  calculateMovement(deltaTime);
  fire();
}

void Hero::calculateMovement(float deltaTime) {
  setTextureRect(m_texRects.at(static_cast<uint8_t>(Direction::Up)));

  constexpr auto spriteWidth = 40;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and m_posY > -spriteWidth) {
    m_posY -= deltaTime * heroSpeed;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and
             m_posY < windowY - spriteWidth) {
    m_posY += deltaTime * heroSpeed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and
      m_posX > -spriteWidth) {
    m_posX -= deltaTime * heroSpeed;
    setTextureRect(m_texRects.at(static_cast<uint8_t>(Direction::Left)));
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and
             m_posX < windowX - spriteWidth) {
    m_posX += deltaTime * heroSpeed;
    setTextureRect(m_texRects.at(static_cast<uint8_t>(Direction::Right)));
  }

  setPosition(m_posX, m_posY);
}

void Hero::fire() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (lastFired + firingCooldown < Game::globalTime) {
      lastFired = Game::globalTime;
      auto projectile = std::make_shared<Projectile>(
          host, m_posX - 50, m_posY + 30, 0, -600, ProjectileLevel::Level1);
      host->addProjectile(projectile);
      firingSound.play();
    }
  }
}

int16_t Hero::health() const { return m_health; }

void Hero::decreaseHealth(int16_t amount) {
  if (amount < 0) {
    std::cout << "healed";
  }

  m_health -= amount;
  if (m_health < 0) {
    m_health = 0;
  }
}
