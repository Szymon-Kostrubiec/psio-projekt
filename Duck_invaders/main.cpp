#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "gamemaster.hpp"
#include "hero.hpp"
#define debug

#ifdef debug
#include "enemy.hpp"
#endif

int main()
{
    GameMaster game(1000, 800);

    auto enemy = std::make_shared<Enemy>(100, 200, 15, 0, 250);
    game.addObject(enemy);

    auto hero = std::make_shared<Hero>(500, 400, 230);
    game.addObject(hero);

    game.enterGameLoop();
    return 0;
}
