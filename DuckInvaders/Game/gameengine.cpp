#include "gameengine.hpp"

GameEngine::GameEngine(uint16_t windowSizeX, uint16_t windowSizeY):
    m_window(sf::VideoMode(windowSizeX, windowSizeY), "Duck invaders")
{
    backgroundTexture.loadFromFile("Textures/background.png");
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, windowSizeX, windowSizeY));
}

void GameEngine::addObject(std::shared_ptr<GameObject> newObject)
{
    m_objects.emplace_back(newObject);
}

void GameEngine::addText(std::shared_ptr<Game::Text> textObj)
{
    m_textObjects.emplace_back(textObj);
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
//        Game::globalTime = gameClock.getElapsedTime().asMilliseconds();

        //let every game object perform a tick
        for (auto const &obj: m_objects) {
            obj->gameTick(this, deltaTime);
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

void GameEngine::removeMe(GameObject *toBeDeleted)
{
    std::cout << "Removed an object";
    std::remove_if(m_objects.begin(), m_objects.end(), [toBeDeleted](std::shared_ptr<GameObject> const &obj){
        return obj.get() == toBeDeleted;    //fast comparisons of pointers, not data
    });
}

void GameEngine::removeMe(Game::Text *toBeDeleted)
{
    std::remove_if(m_textObjects.begin(), m_textObjects.end(), [toBeDeleted](std::shared_ptr<Game::Text> const &obj){
        return obj.get() == toBeDeleted;
    });
}
