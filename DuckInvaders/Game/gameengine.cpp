#include "gameengine.hpp"

namespace Game {
extern uint16_t globalTime;
}

DataLoader const dataloader("ProgramData/data.csv");

GameEngine::GameEngine(uint16_t windowSizeX, uint16_t windowSizeY,
                       Difficulty diff, std::string const &heroTex)
    : gameDifficulty(diff),
      phase(255),
      enemyCount(0),
      m_paused(false),
      m_window(sf::VideoMode(windowSizeX, windowSizeY), "Duck invaders"),
      m_score(0),
      m_scoreText("Score:\n0", 20, 0, 0),
      m_healthText("Health:\n0", 20, 0, 50),
      m_loseText("", 40, windowSizeX / 2, windowSizeY / 2.),
      m_phaseText(4000, "Welcome", 40, windowX / 2, windowY / 5),
      gameSpeedMultiplier(1.0f) {
  backgroundTexture.loadFromFile("Textures/background.jpg");
  backgroundTexture.setRepeated(true);
  background.setTexture(backgroundTexture);
  background.setTextureRect(sf::IntRect(0, 0, windowSizeX, windowSizeY));
  m_scoreText.setPosition(0 + m_phaseText.getLocalBounds().width / 4,
                          0 + m_phaseText.getLocalBounds().height / 2);
  m_healthText.setPosition(0 + m_phaseText.getLocalBounds().width / 4,
                           0 + m_phaseText.getLocalBounds().height * 4 / 2);

  m_hero =
      std::make_shared<Hero>(this, windowSizeX / 2, windowSizeY * 0.9f,
                             dataloader.getHeroHp(gameDifficulty), heroTex);
  addObject(m_hero);

  m_textObjects.emplace_back(&m_scoreText);
  m_textObjects.emplace_back(&m_healthText);
  m_textObjects.emplace_back(&m_phaseText);
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

  while (m_window.isOpen()) {
    sf::Event event;

    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_window.close();
      }
    }

    // dbg
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
      std::cout << std::to_string(enemyCount) << std::endl;
    }

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
    // let every game object perform a tick
    for (auto const &obj : m_objects) {
      if (not m_paused) {
        obj->gameTick(deltaTime * gameSpeedMultiplier);
      }
      m_window.draw(*obj);
    }
    m_scoreText.setString("Score:\n" + std::to_string(m_score));
    m_healthText.setString("Health:\n" + std::to_string(m_hero->health()));
    // draw every text object
    for (auto const &obj : m_textObjects) {
      obj->gameTick();
      m_window.draw(*obj);
    }
    m_window.display();
  }
}

sf::Vector2f GameEngine::getPlayerPos() const { return m_hero->getPosition(); }

void GameEngine::collisionsEngine() {
  if (m_paused) {
    return;
  }

  for (auto const &obj : m_objects) {
    // collisions for hero
    if (obj->getGlobalBounds().intersects(m_hero->getGlobalBounds())) {
      if (auto duck = dynamic_cast<Enemy *>(obj.get())) {
        if (not duck->dead()) {
          if (not dynamic_cast<Boss *>(obj.get())) {
            m_hero->decreaseHealth(
                100 + 50 * static_cast<unsigned int>(gameDifficulty));
            m_score += 50 + static_cast<uint>(gameDifficulty) *
                                50;  // after all, the duck did die
            duck->die();
          } else
            (m_hero->decreaseHealth(10000));
        }
      } else if (auto projectile = dynamic_cast<EnemyProjectile *>(obj.get())) {
        m_hero->decreaseHealth(projectile->damagePotential());
        projectile->expired = true;
      }
    }
  }
  for (auto const &obj : projectiles) {
    if (dynamic_cast<EnemyProjectile *>(obj)) {
      continue;
    }
    if (auto projectile = dynamic_cast<Projectile *>(obj)) {
      for (auto const &gameObj : m_objects) {
        if (gameObj->getGlobalBounds().intersects(obj->getGlobalBounds())) {
          if (auto enemy = dynamic_cast<Enemy *>(gameObj.get())) {
            enemy->takeDamage(projectile->damagePotential());
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
  if (enemyCount not_eq 0) return;

  phase++;

  gameSpeedMultiplier *= 1.1f;

  if (phase % 3 < 2 and phase not_eq 0)
    m_phaseText.addText(2000, "Progressed to a new phase");
  else if (phase % 3 == 2)
    m_phaseText.addText(2000, "Brace yourself, there is a boss coming");

  std::cout << "Progressed to a new phase " << std::to_string(phase)
            << std::endl;

  switch (phase % 3) {
    case 0:
      addObject(std::make_shared<Enemy>(this, randomInt(windowX / 2),
                                        randomInt(windowY / 2),
                                        MovementType::Circle));
      addObject(std::make_shared<Enemy>(this, randomInt(windowX / 2),
                                        randomInt(windowY / 2),
                                        MovementType::Vertical));
      addObject(std::make_shared<Enemy>(this, randomInt(windowX / 2),
                                        randomInt(windowY / 2),
                                        MovementType::Sinusoidal));
      addObject(std::make_shared<Enemy>(this, randomInt(windowX / 2),
                                        randomInt(windowY / 2),
                                        MovementType::Vertical));
      enemyCount = 4;
      break;
    case 1:
      addObject(std::make_shared<Enemy>(this, windowX / 2, windowY / 2,
                                        MovementType::Circle));
      addObject(std::make_shared<Enemy>(this, windowX / 2, windowY / 2,
                                        MovementType::Sinusoidal));
      addObject(std::make_shared<Enemy>(this, windowX / 2, windowY / 2,
                                        MovementType::Sinusoidal));
      enemyCount = 3;
      break;
    case 2:
      MovementCalc *movement;
      while (true) {
        movement = getRandomMovement(MovementType::Vertical);
        auto pos = movement->getCurrentPos();
        auto playerRect = sf::FloatRect(pos, sf::Vector2f(50, 50));
        auto result = true;
        for (auto const &obj : m_objects) {
          if (obj->getGlobalBounds().intersects(playerRect)) result = false;
        }
        if (result)
          break;
        else
          delete movement;
      }

      addObject(std::make_shared<Boss>(this, randomInt(windowX / 2),
                                       randomInt(windowY / 3), movement));

      enemyCount = 1;
      break;
  }
}
