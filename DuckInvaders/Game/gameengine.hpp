#pragma once

#include <cstdint>
#include <list>
#include <memory>
#include <algorithm>
#include "gameObject.hpp"
#include "utility.hpp"
#include "Text.hpp"

#define debug

#ifdef debug
#include "enemy.hpp"
#include "hero.hpp"
#endif

namespace Game{
extern uint32_t globalTime;
}

class GameEngine
{
public:
    explicit GameEngine(uint16_t windowSizeX, uint16_t windowSizeY);
    void addObject(std::shared_ptr<GameObject> newObject);
    void addText(std::shared_ptr<Game::Text> textObj);
    void enterGameLoop();
    void removeMe(GameObject * toBeDeleted);
    void removeMe(Game::Text * toBeDeleted);
private:
    std::list<std::shared_ptr<GameObject>> m_objects;       //list to support frequent, fast deletions and creations
    std::list<std::shared_ptr<Game::Text>> m_textObjects;
    sf::RenderWindow m_window;
    sf::Sprite background;
    sf::Texture backgroundTexture;
};

