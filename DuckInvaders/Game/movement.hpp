#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>

#include "gameengine.hpp"
#include "utility.hpp"

class MovementCalc {
 public:
  explicit MovementCalc(float startX, float startY)
      : m_lastX(startX), m_lastY(startY) {}

  virtual ~MovementCalc() {}
  virtual sf::Vector2f getNextPosition(float step) = 0;

 protected:
  mutable float m_lastX;
  mutable float m_lastY;
};

MovementCalc* getRandomMovement();

class Ellipse final : public MovementCalc {
 public:
  explicit Ellipse(float startX, float startY) : MovementCalc(startX, startY) {}

  virtual sf::Vector2f getNextPosition(float step) override final;

 private:
  bool m_clockwise;
  float a, b, x0, y0;

  friend MovementCalc* getRandomMovement();
};

class Circle final : public MovementCalc {
 public:
  virtual sf::Vector2f getNextPosition(float step) override final;
  explicit Circle(float startX, float startY) : MovementCalc(startX, startY) {}

 private:
  float x0, y0, r;
  float phi;
  float angularVelocity;  // to be initialized by a friend

  friend MovementCalc* getRandomMovement();
};

class Sinusoidal final : public MovementCalc {
 public:
  explicit Sinusoidal(float startX, float startY, float xMin, float xMax,
                      bool direction)
      : MovementCalc(startX, startY),
        m_positiveDirection(direction),
        m_xMin(xMin),
        m_xMax(xMax) {}

  virtual sf::Vector2f getNextPosition(float step) override final;

 private:
  bool m_positiveDirection;
  float m_xMin;
  float m_xMax;
  float sineCoeff;
  float cosineCoeff;
  float m_allCoeff;
  float m_delay;

  friend MovementCalc* getRandomMovement();
};

class RandomMovement final : public MovementCalc {
 public:
  explicit RandomMovement(float startX, float startY, float velocity)
      : MovementCalc(startX, startY), m_velocity(velocity) {}

  virtual sf::Vector2f getNextPosition(float step) override final;

 private:
  float m_velocity;

  friend MovementCalc* getRandomMovement();
};

class VerticalMovement final : public MovementCalc {
 public:
  explicit VerticalMovement(float startX, float startY, float velocity)
      : MovementCalc(startX, startY), m_velocity(velocity) {}

  virtual sf::Vector2f getNextPosition(float step) override final;

 private:
  float m_velocity;

  friend MovementCalc* getRandomMovement();
};
