#pragma once
#include "StaticObjectSpawner.h"

class LaserSpawner : public StaticObjectSpawner {
public:
    LaserSpawner();
    std::vector<std::unique_ptr<StaticObject>> update(float dt, float viewRight) override;

private:
    float m_lastSpawnX = 0.f;
    float m_minDistance = 800.f; 
    float getRandomSpawnInterval();
};
