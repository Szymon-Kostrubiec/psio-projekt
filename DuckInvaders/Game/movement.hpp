#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class MovementCalc {
 public:
  explicit MovementCalc(float startX, float startY)
      : m_lastX(startX), m_lastY(startY) {}

  virtual sf::Vector2f getNextPosition(float step) = 0;

 protected:
  mutable float m_lastX;
  mutable float m_lastY;
};

class Ellipse final : public MovementCalc {
 public:
  explicit Ellipse(float startX, float startY, bool clockwise)
      : MovementCalc(startX, startY), m_clockwise(clockwise) {}

  virtual sf::Vector2f getNextPosition(float step) override final;

 private:
  bool m_clockwise;
     float a, b, x0, y0;

  friend class enemyLoader;
};

class Circle final : public MovementCalc {
 public:
  explicit Circle(float startX, float startY, bool clockwise)
      : MovementCalc(startX, startY), m_clockwise(clockwise) {}

  virtual sf::Vector2f getNextPosition(float step) override final;

 private:
  bool m_clockwise;
     float x0, y0, r;

  friend class enemyLoader;
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

  friend class EnemyLoader;
};
