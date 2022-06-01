#pragma once

#include <cstdint>

enum class ProjectileLevel: uint8_t {Level1, Level2, Level3, Level4};
enum class Difficulty: uint8_t {Easy, Medium, Hard};

int randomInt(int max, int min = 0);
double randomDouble(double max, double min = 0);
