#pragma once

#include "utility.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static constexpr auto numberOfDifficulties = 3;

class DataLoader {
public:
  DataLoader(std::string const &fileName);

  uint16_t getHeroHp(Difficulty diff) const {
    return heroHp.at(static_cast<uint8_t>(diff));
  }
  uint16_t getScoreIncrease(Difficulty diff) const {
    return scoreIncrease.at(static_cast<uint8_t>(diff));
  }
  uint16_t getEnemyHp(Difficulty diff) const {
    return enemyHp.at(static_cast<uint8_t>(diff));
  }
  uint16_t getBossHp(Difficulty diff) const {
    return bossHp.at(static_cast<uint8_t>(diff));
  }
  uint16_t getProjectileSpeed(Difficulty diff) const {
    return projectileSpeed.at(static_cast<uint8_t>(diff));
  }

private:
  // entire data file is loaded because the difficulty may change in a lifetime
  // of the program

  std::vector<uint16_t> heroHp;
  std::vector<uint16_t> scoreIncrease;
  std::vector<uint16_t> enemyHp;
  std::vector<uint16_t> bossHp;
  std::vector<uint16_t> projectileSpeed;
};
