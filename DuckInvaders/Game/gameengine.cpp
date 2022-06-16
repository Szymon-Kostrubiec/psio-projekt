#include "gameengine.hpp"

namespace Game {
extern uint16_t globalTime;
}

GameEngine::GameEngine(uint16_t windowSizeX, uint16_t windowSizeY,
                       Difficulty diff, std::string const &heroTex)
    : gameDifficulty(diff),
      phase(0),
      enemyCount(0),
      m_paused(false),
      m_window(sf::VideoMode(windowSizeX, windowSizeY), "Duck invaders"),
      m_score(0),
      m_scoreText("Score:\n0", 20, 0, 0),
      m_healthText("Health:\n0", 20, 0, 45),
      m_loseText("", 40, windowSizeX / 2, windowSizeY / 2) {

  backgroundTexture.loadFromFile("Textures/background.jpg");
  backgroundTexture.setRepeated(true);
  background.setTexture(backgroundTexture);
  background.setTextureRect(sf::IntRect(0, 0, windowSizeX, windowSizeY));

  auto health = 750 - 250 * static_cast<int>(gameDifficulty);
  m_hero = std::make_shared<Hero>(this, windowSizeX / 2, windowSizeY * 0.9f,
                                  health, heroTex);
  addObject(m_hero);

  // showcase
  //    auto duck = std::make_shared<Enemy>(this, windowSizeX/2, 200);
  //    addObject(duck);

  m_textObjects.emplace_back(&m_scoreText);
  m_textObjects.emplace_back(&m_healthText);
}

void GameEngine::addObject(const std::shared_ptr<GameObject> &newObject) {
  m_objects.emplace_back(newObject);
}

void GameEngine::addText(Game::Text *textObj) {
  m_textObjects.emplace_back(textObj);
}

void GameEngine::enterGameLoop() {
  sf::Clock fpsClock;
  sf::Clock gameClock;

  // dbg

  while (m_window.isOpen()) {
    sf::Event event;

    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_window.close();
        // todo: add handling
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) and randomInt(200) < 1)
      enemyCount = 0;

    cleanup();
    spawnEnemies();

    m_window.clear(sf::Color::Black);
    m_window.draw(background);

    // update global timers and get fps data
    const auto time = fpsClock.restart();
    const auto deltaTime = time.asSeconds();

    Game::globalTime = gameClock.getElapsedTime().asMilliseconds();

    collisionsEngine();

    checkLose();

    if (not m_paused) {
      // let every game object perform a tick
      enemyCount = 0;
      for (auto const &obj : m_objects) {
        obj->gameTick(deltaTime);
        if (dynamic_cast<Enemy *>(obj.get())) enemyCount++;
      }
    }
    // draw every game object
    for (auto const &obj : m_objects) {
      m_window.draw(*obj);
    }
    m_scoreText.setString("Score:\n" + std::to_string(m_score));
    m_healthText.setString("Health:\n" + std::to_string(m_hero->health()));
    // draw every text object
    for (auto const &obj : m_textObjects) {
      m_window.draw(*obj);
    }
    m_window.display();
  }
}

void GameEngine::collisionsEngine() {
  if (m_paused) {
    return;
  }

  for (auto const &obj : m_objects) {
    // collisions for hero
    if (obj->getGlobalBounds().intersects(m_hero->getGlobalBounds())) {
      if (auto duck = dynamic_cast<Enemy *>(obj.get())) {
        if (not duck->dead()) {
          m_hero->decreaseHealth(
              100 + 50 * static_cast<unsigned int>(gameDifficulty));
          m_score += 50 + static_cast<uint>(gameDifficulty) *
                              50;  // after all, the duck did die
          duck->die();
        }
      } else if (auto projectile = dynamic_cast<EnemyProjectile *>(obj.get())) {
        m_hero->decreaseHealth(projectile->damagePotential());
        projectile->expired = true;
      }
    }
  }
  for (auto const &obj : projectiles) {
    if (auto projectile = dynamic_cast<Projectile *>(obj)) {
      for (auto const &gameObj : m_objects) {
        if (gameObj->getGlobalBounds().intersects(obj->getGlobalBounds())) {
          if (auto enemy = dynamic_cast<Enemy *>(gameObj.get())) {
            enemy->decreaseHealth(projectile->damagePotential());
            projectile->expired = true;
            m_score += 50 + 50 * static_cast<uint>(gameDifficulty);
            continue;
          }
        }
      }
    }
  }
}

void GameEngine::cleanup() {
  projectiles.remove_if([](GameObject const *obj) { return obj->expired; });
  m_objects.remove_if(
      [](std::shared_ptr<GameObject> const &obj) { return obj->expired; });
}

void GameEngine::checkLose() {
  if (m_hero->health() <= 0) {
    m_paused = true;

    m_loseText.setString("You lost.\nScore: " + std::to_string(m_score));

    addText(&m_loseText);  // display lose text
  }
}

void GameEngine::spawnEnemies() {
  if (enemyCount > 0) return;

  phase++;

  auto newEnemies =
      (static_cast<uint>(gameDifficulty) + phase) * randomInt(3, 1);

  for (std::size_t iter = 0; iter < newEnemies; ++iter) {
    auto enemy = std::make_shared<Enemy>(this, randomInt(windowX * 0.9f),
                                         randomInt(windowY * 0.5f));
    enemyCount++;
    addObject(enemy);
  }
}
