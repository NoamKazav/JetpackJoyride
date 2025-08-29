#include "Spawners/ScientistSpawner.h"
#include "factory/GameFactory.h"
#include "Objects/MovingObject.h"
#include "Utils/GameConstants.h"

bool regScientistSpawner = GameFactory<MovingObjectSpawner>::registerit(
    "ScientistSpawner", []() -> std::unique_ptr<MovingObjectSpawner> {
        return std::make_unique<ScientistSpawner>();
    });

ScientistSpawner::ScientistSpawner() {
    m_nextSpawnTime = getRandomSpawnTime(); 
}

float ScientistSpawner::getRandomSpawnTime() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(GameConstants::SCIENTIST_SPAWN_MIN_INTERVAL,
        GameConstants::SCIENTIST_SPAWN_MAX_INTERVAL);

    return dist(gen);
}

std::vector<std::unique_ptr<MovingObject>> ScientistSpawner::update(float dt, float viewRight) {
    m_elapsed += dt;

    std::vector<std::unique_ptr<MovingObject>> result;

    if (m_elapsed >= m_nextSpawnTime) {
        m_elapsed = 0.f;
        m_nextSpawnTime = getRandomSpawnTime(); 

        auto obj = GameFactory<MovingObject>::create("Scientist");
        if (!obj)
            throw std::runtime_error("ScientistSpawner failed to create Scientist object");

        if (obj) {
           float groundY = GameConstants::GROUND_Y;
           float startX = viewRight + GameConstants::SCIENTIST_SPAWN_OFFSET_X;
           obj->setPosition({ startX, groundY - obj->getSprite().getGlobalBounds().height });
           result.push_back(std::move(obj));
        }
    }

    return result;
}
