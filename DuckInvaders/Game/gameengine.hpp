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
    void addObject(std::shared_ptr<GameObject> newObject);
    void addText(Game::Text * textObj);
    void enterGameLoop();

    Difficulty const gameDifficulty;

private:
    void collisionsEngine();
    void cleanup();

    bool m_paused;

    std::shared_ptr<Hero> m_hero;
    std::list<std::shared_ptr<GameObject>> m_objects;       //list to support frequent, fast deletions and creations
    std::list<Game::Text *> m_textObjects;
    sf::RenderWindow m_window;
    sf::Sprite background;
    sf::Texture backgroundTexture;

    uint32_t m_score;
    Game::Text m_scoreText;
    Game::Text m_healthText;
};

