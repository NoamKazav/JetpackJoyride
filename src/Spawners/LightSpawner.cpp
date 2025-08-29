#include "Spawners/LightSpawner.h"
#include "factory/GameFactory.h"
#include "Utils/GameConstants.h"
#include <cmath>
#include <iostream>

bool regLightSpawner = GameFactory<StaticObjectSpawner>::registerit(
    "LightSpawner", []() -> std::unique_ptr<StaticObjectSpawner> {
        return std::make_unique<LightSpawner>();
    });

LightSpawner::LightSpawner() {}

std::vector<std::unique_ptr<StaticObject>> LightSpawner::update(float dt, float viewRight) {
    std::vector<std::unique_ptr<StaticObject>> result;

    m_timer += dt;  
    if (m_timer >= m_interval) {
        m_timer = 0.f;

        auto light = GameFactory<StaticObject>::create("Light");
        if (!light)
            throw std::runtime_error("lightSpawner failed to create light object");
        float x = viewRight;
        float y = GameConstants::LIGHT_SPAWN_Y;
        light->setPosition({ x, y });

        result.push_back(std::move(light));
    }

    return result;
}