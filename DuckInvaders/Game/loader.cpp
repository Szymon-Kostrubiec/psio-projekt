#include "loader.hpp"

static const std::array<std::string, 5> enemyFileNames{"Level1.csv", "Level2.csv", "Level3.csv", "Level4.csv", "Level5.csv"};

namespace Game {

std::vector<std::shared_ptr<Enemy>> getEnemies(Level level) {

    std::fstream file(enemyFileNames.at(static_cast<uint8_t>(level)));
    if (not(file.is_open())) {
        std::cerr << "File " << enemyFileNames.at(static_cast<uint8_t>(level)) << " not opened" << std::endl;
        return std::vector<std::shared_ptr<Enemy>>();
    } //todo
}

}   //namespace game
