#pragma once

#include "gameObject.hpp"

class Hero: public GameObject
{
public:
    Hero();
    void gameTick(sf::RenderWindow * host, float deltaTime) override;
private:
    void calculateMovement(float deltaTime) override;

    uint16_t health;
};

