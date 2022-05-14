#pragma once

#include "gameObject.hpp"
#include "gamemaster.hpp"

class Hero: public GameObject
{
public:
    Hero(uint16_t posX, uint16_t posY, uint16_t health);
    void gameTick(GameMaster * host, float deltaTime) override;
private:
    void calculateMovement(float deltaTime) override;
    void loadTextures();
    uint16_t m_health;
    sf::Texture texture;
    static constexpr uint16_t heroSpeed{200};
};

