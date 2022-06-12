#include "movement.hpp"

inline static float delay(float argument, float delay) {
    return argument - delay;    //todo: ???
}
inline static float radians(float degrees) {
    return degrees * 3.1415 / 180;
}

sf::Vector2f Sinusoidal::getNextPosition(float step)
{
    if (m_lastX > m_xMax)
        m_positiveDirection = false;
    else if (m_lastX < m_xMin)
        m_positiveDirection = true;

    if (m_positiveDirection)
        m_lastX += step;
    else m_lastX -= step;

    return sf::Vector2f(m_lastX, (m_lastY = m_allCoeff * sin(m_lastX) * cos(m_lastX) - m_delay));
}

sf::Vector2f Circle::getNextPosition(float step)
{

}

sf::Vector2f Ellipse::getNextPosition(float step)
{
    return sf::Vector2f();
}
