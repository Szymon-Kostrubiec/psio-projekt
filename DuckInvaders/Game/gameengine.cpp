#include "gameengine.hpp"

namespace Game {
extern uint16_t globalTime;
}

GameEngine::GameEngine(uint16_t windowSizeX, uint16_t windowSizeY, Difficulty diff, std::string const &heroTex):
    gameDifficulty(diff), m_paused(false), m_window(sf::VideoMode(windowSizeX, windowSizeY), "Duck invaders"),
    m_score(0), m_scoreText("Score:\n0", 20, 0, 0), m_healthText("Health:\n0", 20, 0, 45)
{
    backgroundTexture.loadFromFile("Textures/background.jpg");
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, windowSizeX, windowSizeY));

    auto health = 750 - 250 * static_cast<int>(gameDifficulty);
    m_hero = std::make_shared<Hero>(this, windowSizeX/2, windowSizeY/2, health, heroTex);
    addObject(m_hero);

    //showcase
    auto duck = std::make_shared<Enemy>(this, windowSizeX/2, 200);
    addObject(duck);

    m_textObjects.emplace_back(&m_scoreText);
    m_textObjects.emplace_back(&m_healthText);
}

void GameEngine::addObject(std::shared_ptr<GameObject> newObject)
{
    m_objects.emplace_back(newObject);
}

void GameEngine::addText(Game::Text * textObj)
{
    m_textObjects.emplace_back(textObj);
}

void GameEngine::enterGameLoop()
{
    sf::Clock fpsClock;
    sf::Clock gameClock;

    //dbg


    while (m_window.isOpen()) {

        sf::Event event;

        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
                //todo: add handling
            }
        }

        m_window.clear(sf::Color::Black);
        m_window.draw(background);

        //update global timers and get fps data
        const auto time = fpsClock.restart();
        const auto deltaTime = time.asSeconds();

        Game::globalTime = gameClock.getElapsedTime().asMilliseconds();

        collisionsEngine();
        if(not m_paused) {
            //let every game object perform a tick
            for (auto const &obj: m_objects) {
                obj->gameTick(deltaTime);
            }
        }
        //draw every game object
        for (auto const &obj: m_objects) {
            m_window.draw(*obj);
        }
        m_scoreText.setString("Score:\n" + std::to_string(m_score));
        m_healthText.setString("Health:\n" + std::to_string(m_hero->health()));
        //draw every text object
        for (auto const &obj: m_textObjects) {
            m_window.draw(*obj);
        }
        m_window.display();
    }
}

void GameEngine::collisionsEngine()
{
    for (auto const &obj: m_objects) {

        if (obj->getGlobalBounds().intersects(m_hero->getGlobalBounds())) {

            if (auto duck = dynamic_cast<Enemy *>(obj.get())) {

            }
            else if (auto projectile = dynamic_cast<Projectile *>(obj.get())) {
                m_hero->decreaseHealth(projectile->damagePotential());
            }
        }
    }
}

void GameEngine::cleanup()
{
    std::remove_if(m_objects.begin(), m_objects.end(), [](std::shared_ptr<GameObject> const &obj){
        return obj->expired;
    });
}

