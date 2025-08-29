#include "Spawners/SpawnerManager.h"

void SpawnerManager::addStaticSpawner(std::unique_ptr<StaticObjectSpawner> spawner) {
    m_staticSpawners.push_back(std::move(spawner));
}

void SpawnerManager::addMovingSpawner(std::unique_ptr<MovingObjectSpawner> spawner) {
    m_movingSpawners.push_back(std::move(spawner));
}

std::vector<std::unique_ptr<StaticObject>> SpawnerManager::spawnStatic(float dt, float viewRight) {
    std::vector<std::unique_ptr<StaticObject>> result;
    for (auto& spawner : m_staticSpawners) {
        auto newObjs = spawner->update(dt, viewRight);
        result.insert(result.end(),
            std::make_move_iterator(newObjs.begin()),
            std::make_move_iterator(newObjs.end()));
    }
    return result;
}

std::vector<std::unique_ptr<MovingObject>> SpawnerManager::spawnMoving(float dt, float viewRight) {
    std::vector<std::unique_ptr<MovingObject>> result;
    for (auto& spawner : m_movingSpawners) {
        auto newObjs = spawner->update(dt, viewRight);
        result.insert(result.end(),
            std::make_move_iterator(newObjs.begin()),
            std::make_move_iterator(newObjs.end()));
    }
    return result;
}
