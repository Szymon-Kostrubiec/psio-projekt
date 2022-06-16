#pragma once

#include "gameObject.hpp"
#include "movement.hpp"
#include "projectile.hpp"
#include "utility.hpp"
#include <iostream>
#include <memory>

enum class State : uint8_t { Idle1, Idle2, AboutToFire, Dead };
// params
static constexpr int animationFrequency = 2000;

enum class Level : uint8_t { Level1, Level2, Level3, Level4, Level5 };

class Enemy : public GameObject {
public:
  explicit Enemy(GameEngine *host, uint16_t startX, uint16_t startY);
  virtual ~Enemy();
  void gameTick(float deltaTime) override;
  void takeDamage(uint16_t dmg) { m_health -= dmg; }
  void die();
  bool dead() const { return state == State::Dead; }
  void decreaseHealth(uint16_t amount) { m_health -= amount; }

protected:
  void loadTextures();
  void animate();
  void spawnProjectile();
  const uint32_t projectileTimeout;
  static constexpr auto projectileChance = 0.3;
  uint32_t lastProjectileFired;
  int16_t m_health;

  std::array<sf::Texture, 2> m_textures;
  sf::Texture textureDead;
  State state;
  uint32_t timeOfDeath;

  MovementCalc *movement;
  int16_t m_vel;

  friend class EnemyBuilder;
};

class Boss final : public Enemy {
public:
  explicit Boss(GameEngine *host, uint16_t startX, uint16_t startY);
  virtual ~Boss() {}

  virtual void gameTick(float deltaTime) override final;

private:
  void spawnProjectile();
  static constexpr auto projectileChance = 0.6;
  const uint32_t projectileTimeout;
};
