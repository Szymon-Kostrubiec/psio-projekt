#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "gamewindow.hpp"

#define debug

#ifdef debug
#include "enemy.hpp"
#endif

int main()
{
    GameWindow game(1000, 800);
    auto enemy = std::make_shared<Enemy>(100, 200, 15, 0, 250);

    game.addObject(enemy);
    game.enterGameLoop();
    return 0;
}
