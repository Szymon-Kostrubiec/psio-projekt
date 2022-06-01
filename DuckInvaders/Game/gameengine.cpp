#include "gameengine.hpp"

GameEngine::GameEngine(uint16_t windowSizeX, uint16_t windowSizeY, Difficulty diff, std::string const &heroTex):
    gameDifficulty(diff), m_window(sf::VideoMode(windowSizeX, windowSizeY), "Duck invaders")
{
    backgroundTexture.loadFromFile("Textures/background.png");
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, windowSizeX, windowSizeY));

    auto health = 750 - 250 * static_cast<int>(gameDifficulty);
    m_hero = std::make_shared<Hero>(this, windowSizeX/2, windowSizeY/2, health, heroTex);
}

void GameEngine::addObject(std::unique_ptr<GameObject> &&newObject)
{
    m_objects.emplace_back(std::move(newObject));
}

void GameEngine::addText(std::unique_ptr<Game::Text> &&textObj)
{
    m_textObjects.emplace_back(std::move(textObj));
}

void GameEngine::enterGameLoop()
{
    sf::Clock fpsClock;
    sf::Clock gameClock;
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

        collisionsEngine();

        //let every game object perform a tick
        m_hero->gameTick(deltaTime);
        for (auto const &obj: m_objects) {
            obj->gameTick(deltaTime);
        }
        //draw every game object
        for (auto const &obj: m_objects) {
            m_window.draw(*obj);
        }
        //draw every text object
        for (auto const &obj: m_textObjects) {
            obj->gameTick();
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

