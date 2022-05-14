#include "gamewindow.hpp"

GameWindow::GameWindow(uint16_t windowSizeX, uint16_t windowSizeY):
    m_window(sf::VideoMode(windowSizeX, windowSizeY), "Duck invaders")
{

}

void GameWindow::addObject(std::shared_ptr<GameObject> newObject)
{
    m_objects.emplace_back(newObject);
}

void GameWindow::enterGameLoop()
{
    sf::Clock fpsClock;
    while (m_window.isOpen()) {

        sf::Event event;

        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
                //todo: add handling
            }
        }

        m_window.clear(sf::Color::Black);

        for (auto const &obj: m_objects) {
            obj->gameTick(&m_window, fpsClock.restart().asSeconds());
        }

        for (auto const &obj: m_objects) {
            m_window.draw(*obj);
        }

        m_window.display();
    }
}
