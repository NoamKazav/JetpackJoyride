#pragma once

#include "Spawners/MovingObjectSpawner.h"
#include "Utils/GameConstants.h"
#include <random>

class ScientistSpawner : public MovingObjectSpawner {
public:
    ScientistSpawner();

    std::vector<std::unique_ptr<MovingObject>> update(float dt, float viewRight) override;

private:
    float m_elapsed = 0.f;
    float m_nextSpawnTime = 0.f;
    float m_lastSpawnX = 0.f;

    float getRandomSpawnTime();
};
