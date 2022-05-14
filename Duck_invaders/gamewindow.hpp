#pragma once

#include <cstdint>
#include "gameObject.hpp"
#include <vector>
#include <memory>

#define debug

#ifdef debug
#include "enemy.hpp"
#endif
class GameWindow
{
public:
    explicit GameWindow(uint16_t windowSizeX, uint16_t windowSizeY);
    void addObject(std::shared_ptr<GameObject> newObject);
    void enterGameLoop();
private:
    std::vector<std::shared_ptr<GameObject>> m_objects;
    sf::RenderWindow m_window;
};

