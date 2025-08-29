#pragma once
#include "Spawners/StaticObjectSpawner.h"
#include "Spawners/MovingObjectSpawner.h"
#include <vector>
#include <memory>

class SpawnerManager {
public:
    void addStaticSpawner(std::unique_ptr<StaticObjectSpawner> spawner);
    void addMovingSpawner(std::unique_ptr<MovingObjectSpawner> spawner);

    std::vector<std::unique_ptr<StaticObject>> spawnStatic(float dt, float viewRight);
    std::vector<std::unique_ptr<MovingObject>> spawnMoving(float dt, float viewRight);

private:
    std::vector<std::unique_ptr<StaticObjectSpawner>> m_staticSpawners;
    std::vector<std::unique_ptr<MovingObjectSpawner>> m_movingSpawners;
};
