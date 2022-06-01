#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

class GameEngine;

class GameObject: public sf::Sprite {
public:
    virtual void gameTick(GameEngine * host, float deltaTime) = 0;

protected:
    GameObject(uint16_t startPosX, uint16_t startPosY) : //check the types
        m_posX(startPosX), m_posY(startPosY) {
    }
    virtual ~GameObject() {}
    virtual void calculateMovement(float deltaTime) = 0; //todo
    float m_posX, m_posY;
    sf::Texture m_texture;
};
