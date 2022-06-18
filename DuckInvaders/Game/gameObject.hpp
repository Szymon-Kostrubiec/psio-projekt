#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

class GameEngine;

class GameObject : public sf::Sprite {
public:
  virtual void gameTick(float deltaTime) = 0;
  virtual ~GameObject() {}
  bool expired;

protected:
  GameObject(GameEngine *host, float startPosX, float startPosY)
      : expired(false), m_posX(startPosX), m_posY(startPosY), host(host) {
    setPosition(m_posX, m_posY);
  }
  float m_posX, m_posY;
  sf::Texture m_texture;
  GameEngine *host;
};
