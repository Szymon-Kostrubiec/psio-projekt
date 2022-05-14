#pragma once

#include "enemy.hpp"

enum class Level : uint8_t {Level1, Level2, Level3};

class EnemySpawner {

public:
    static EnemySpawner * getInstance();
    ~EnemySpawner();
    Enemy getEnemy(uint8_t count);

private:
    EnemySpawner();
    static EnemySpawner * m_instance;
};
