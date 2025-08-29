#pragma once
#include "Spawners/StaticObjectSpawner.h"

class GiftSpawner : public StaticObjectSpawner {
public:
    std::vector<std::unique_ptr<StaticObject>> update(float dt, float viewRight) override;

private:
    float m_timeSinceLast = 0.f;
    float m_spawnInterval = 14.0f; 
    static bool m_registerit;
};
