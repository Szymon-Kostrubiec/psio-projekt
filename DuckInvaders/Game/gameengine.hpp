#pragma once

#include <cstdint>
#include <list>
#include <memory>
#include <algorithm>
#include "gameObject.hpp"
#include "utility.hpp"
#include "Text.hpp"

#include "enemy.hpp"
#include "hero.hpp"

class Hero;

class GameEngine
{
public:
    explicit GameEngine(uint16_t windowSizeX, uint16_t windowSizeY, Difficulty diff, std::string const &heroTex);
    void addObject(std::unique_ptr<GameObject> &&newObject);
    void addText(std::unique_ptr<Game::Text> &&textObj);
    void enterGameLoop();

    Difficulty const gameDifficulty;

private:
    void collisionsEngine();

    std::shared_ptr<Hero> m_hero;
    std::list<std::unique_ptr<GameObject>> m_objects;       //list to support frequent, fast deletions and creations
    std::list<std::unique_ptr<Game::Text>> m_textObjects;
    sf::RenderWindow m_window;
    sf::Sprite background;
    sf::Texture backgroundTexture;
};

