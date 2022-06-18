#include "movement.hpp"

inline static float radians(float degrees) { return degrees * 3.1415 / 180; }

static constexpr auto spawnableX = windowX * 0.8; // todo: lower bound
static constexpr auto spawnableY = windowY * 0.6;
static constexpr auto maxEnemyLinearVel = 200;
static constexpr auto maxEnemyAngularVel = 90;
static constexpr auto minEnemyAngularVel = 45;

static inline float sineValue(float x, float a, float b) {
  return a * sin(b * x);
}
static inline float integrandValue(float x, float a, float b) {
  return sqrt(1.0f + a * b * cos(b * x));
}
static constexpr auto increment = 0.0001f;

static float estimateIntegral(double startX, double a, double b,
                              double translation);

sf::Vector2f Sinusoidal::getNextPosition(float step) {

  if (m_lastX < m_xMin) {
    m_velocity = std::abs(m_velocity);
  } else if (m_lastX > m_xMax) {
    m_velocity = -std::abs(m_velocity);
  }
  // trivialisation

#ifdef Verbatim

  auto previousX = m_lastX;
  auto previousY = m_lastY;

#endif

  m_lastX += estimateIntegral(m_lastX, m_allCoeff, m_sineCoeff,
                              step * m_velocity * 10) /
             10;
  m_lastY = 400 + sineValue(m_lastX, m_allCoeff,
                            m_sineCoeff); // 400 => window positon offset

#ifdef Verbatim

  std::cout << "Translation length over delta time: "
            << sqrt(pow(m_lastX - previousX, 2) + pow(m_lastY - previousY, 2)) /
                   step;

#endif

  return sf::Vector2f(m_lastX, m_lastY);
}

sf::Vector2f Circle::getNextPosition(float step) {
  phi += angularVelocity * step;
  // translate polar coordintates:
  auto y = r * sin(radians(phi));
  auto x = r * cos(radians(phi));

  return sf::Vector2f(x + x0, y + y0);
}

sf::Vector2f Ellipse::getNextPosition([[maybe_unused]] float step) {
  return sf::Vector2f();
}

sf::Vector2f RandomMovement::getNextPosition([[maybe_unused]] float step) {
  auto x = randomDouble(m_velocity, -m_velocity);

  // calculate corresponding y so that the velocity stays constant

  auto y = sqrt(m_velocity * m_velocity - x * x);

  m_lastX += x;
  m_lastY += y;

  return sf::Vector2f(m_lastX, m_lastY);
}

sf::Vector2f VerticalMovement::getNextPosition(float step) {
  if (m_lastX < 0)
    m_velocity = std::abs(m_velocity);
  if (m_lastX > windowX)
    m_velocity = -std::abs(m_velocity);

  return sf::Vector2f((m_lastX += m_velocity * step), m_lastY);
}

MovementCalc *getRandomMovement() {
  auto randomX = randomDouble(spawnableX);
  auto randomY = randomDouble(spawnableY);
  switch (/*randomInt(3)*/ 3) {
  case 0: {
    auto circle = new Circle(randomX, randomY);
    circle->x0 = randomX;
    circle->y0 = randomY;
    circle->r = randomDouble(150);
    circle->angularVelocity =
        randomDouble(maxEnemyAngularVel, minEnemyAngularVel);
    circle->phi = randomDouble(360);
    return circle; // to be deleted in caller
  }
  case 1:
    return new RandomMovement(randomX, randomY,
                              randomDouble(maxEnemyLinearVel));
  case 2:
  case 3: {
    auto sine = new Sinusoidal(randomX, 400, windowX * .1f, windowX * .9f);
    sine->m_sineCoeff = randomDouble(0.015, 0.01);
    sine->m_allCoeff = randomDouble(200, 100);
    sine->m_velocity = randomDouble(150, 80) * ((randomInt(10) < 5) ? 1 : -1);

    return sine;
  }
  default:

    return new VerticalMovement(
        randomX, randomY,
        randomDouble(maxEnemyLinearVel)); // to be deleted in caller
  }
}

static float estimateIntegral(double startX, double a, double b,
                              double translation) {
  // function to estimate x, x > startX, satisfying integral ~ translation
  double currentTranslation{0.f};
  double currentX{0.f};

  // if integrating a < b
  if (translation > 0) {
    while (currentTranslation < translation) {

      currentTranslation += integrandValue(currentX, a, b) * increment;
      currentX += increment;
    }
  } else {
    while (currentTranslation > translation) {
      currentTranslation -= integrandValue(currentX, a, b) * increment;
      currentX -= increment;
    }
  }
  return currentX; // todo: first x satisfying currentTranslation < translation
                   // isn't always the closest
}
