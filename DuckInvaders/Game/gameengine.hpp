﻿#pragma once

#include <algorithm>
#include <cstdint>
#include <list>
#include <memory>

#include "Text.hpp"
#include "dataloader.h"
#include "enemy.hpp"
#include "gameObject.hpp"
#include "hero.hpp"
#include "utility.hpp"

class Hero;
class Projectile;
class MovementCalc;

class GameEngine {
 public:
  explicit GameEngine(uint16_t windowSizeX, uint16_t windowSizeY,
                      Difficulty diff, std::string const &heroTex);
  void addObject(std::shared_ptr<GameObject> const &newObject);
  void addProjectile(std::shared_ptr<GameObject> const &newProj) {
    addObject(newProj);
    projectiles.emplace_back(newProj.get());
  }
  void addText(Game::Text *textObj);
  void enterGameLoop();

  void decreaseEnemyCount() { enemyCount--; }
  sf::Vector2f getPlayerPos() const;  // for "homing" missiles

  Difficulty const gameDifficulty;

 private:
  void collisionsEngine();
  void cleanup();
  void checkLose();

  void spawnEnemies();
  uint8_t phase;
  uint8_t enemyCount;

  bool m_paused;

  std::shared_ptr<Hero> m_hero;
  std::list<std::shared_ptr<GameObject>>
      m_objects;  // list to support frequent, fast deletions and creations
  std::list<Game::Text *> m_textObjects;
  std::list<GameObject *> projectiles;
  sf::RenderWindow m_window;
  sf::Sprite background;
  sf::Texture backgroundTexture;

  uint32_t m_score;
  Game::Text m_scoreText;
  Game::Text m_healthText;
  Game::Text m_loseText;
  Game::AnimatedText m_phaseText;

  float gameSpeedMultiplier;
};
