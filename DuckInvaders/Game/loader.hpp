#pragma once

#include <memory>
#include <fstream>
#include <array>
#include "projectile.hpp"
#include "enemy.hpp"

namespace Game {

std::vector<std::shared_ptr<Enemy>> getEnemies(Level level);

std::vector<std::shared_ptr<Projectile>> getProjectile(Difficulty difficulty, Level level);
}
