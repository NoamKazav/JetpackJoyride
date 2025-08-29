#pragma once

#include "Spawners/StaticObjectSpawner.h"
#include "Objects/Light.h"
#include "Objects/StaticObject.h"
#include <memory>

class LightSpawner : public StaticObjectSpawner {
public:
    LightSpawner();
    std::vector<std::unique_ptr<StaticObject>> update(float dt, float viewRight) override;

private:
    float m_timer = 0.f;
    const float m_interval = 9.0f; 
};
