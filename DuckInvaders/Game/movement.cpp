#include "movement.hpp"

inline static float radians(float degrees) { return degrees * 3.1415 / 180; }

static constexpr auto spawnableX = windowX * 0.8; //todo: lower bound
static constexpr auto spawnableY = windowY * 0.6;
static constexpr auto maxEnemyLinearVel = 200;
static constexpr auto maxEnemyAngularVel = 90;
static constexpr auto minEnemyAngularVel = 45;

static inline float sineValue(float x, float a, float b) {
    return a * sin(b*x);
}
static inline float integrandValue(float x, float a, float b) {
    return sqrt(1.0f + a*b*cos(b*x));
}
static constexpr auto increment = 0.01f;

static float estimateIntegral(float startX, float a, float b, float translation);

sf::Vector2f Sinusoidal::getNextPosition(float step) {
    auto curveLength = step * m_velocity;
    auto nextX = estimateIntegral(m_lastX, m_allCoeff, m_sineCoeff, curveLength);

    return sf::Vector2f((m_lastX = nextX), sineValue(nextX, m_allCoeff, m_sineCoeff));
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
  if (m_lastX < 0) m_velocity = std::abs(m_velocity);
  if (m_lastX > windowX) m_velocity = -std::abs(m_velocity);

  return sf::Vector2f((m_lastX += m_velocity * step), m_lastY);
}

MovementCalc *getRandomMovement() {
  auto randomX = randomDouble(spawnableX);
  auto randomY = randomDouble(spawnableY);
  switch (randomInt(3)) {
    case 0: {
      auto circle = new Circle(randomX, randomY);
      circle->x0 = randomX;
      circle->y0 = randomY;
      circle->r = randomDouble(150);
      circle->angularVelocity =
          randomDouble(maxEnemyAngularVel, minEnemyAngularVel);
      circle->phi = randomDouble(360);
      return circle;  // to be deleted in caller
    }
    case 1:
      return new RandomMovement(randomX, randomY,
                                randomDouble(maxEnemyLinearVel));
    case 2:
    case 3: {
        auto sine = new Sinusoidal(randomX, randomY, windowX*.1f, windowX * .9f, (randomInt(10) < 5));
        sine->m_sineCoeff = randomDouble(40, 1);
        sine->m_allCoeff = randomDouble(4, 1);
        sine->m_velocity = randomDouble(20) * ((randomInt(10) < 5) ? 1 : -1);
        return sine;
    }
    default:

     return new VerticalMovement(
          randomX, randomY,
          randomDouble(maxEnemyLinearVel));  // to be deleted in caller
  }
}


static float estimateIntegral(float startX, float a, float b, float translation) {
    //function to estimate x, x > startX, satisfying integral ~ translation
    auto currentTranslation = 0.f;
    auto currentX = startX;

    while (currentTranslation < translation) {

        currentTranslation += integrandValue(currentX, a, b) * increment;
        currentX += increment;
    }
    return currentX;    //todo: first x satisfying currentTranslation < translation isn't always the closest
}
