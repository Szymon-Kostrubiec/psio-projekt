#pragma once

#include <SFML/Window.hpp>
#include <cstdint>
#include <random>

enum class ProjectileLevel : uint8_t { Level1, Level2, Level3, Level4 };
enum class Difficulty : uint8_t { Easy, Medium, Hard };
enum class MovementType : uint8_t { Circle, Sinusoidal, Vertical, Random };

constexpr auto windowX = 1000;
constexpr auto windowY = 800;

int randomInt(int max, int min = 0);
double randomDouble(double max, double min = 0);

inline sf::Vector2f normalizeVector(sf::Vector2f const vector) {
  auto length = sqrt(vector.x * vector.x + vector.y * vector.y);

  return sf::Vector2f(vector.x / length, vector.y / length);
}
