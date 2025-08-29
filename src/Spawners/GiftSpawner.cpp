#include "Spawners/GiftSpawner.h"
#include "factory/GameFactory.h"
#include <cstdlib>  
#include <ctime>    
#include "Objects/Gift.h"
#include <stdexcept> 
#include "Utils/GameConstants.h"

bool GiftSpawner::m_registerit = GameFactory<StaticObjectSpawner>::registerit(
    "GiftSpawner",
    []() -> std::unique_ptr<StaticObjectSpawner> {
        return std::make_unique<GiftSpawner>();
    }
);

std::vector<std::unique_ptr<StaticObject>> GiftSpawner::update(float dt, float viewRight) {
    GiftType type = static_cast<GiftType>(rand() % GameConstants::NUM_GIFT_TYPES);
    m_timeSinceLast += dt;

    if (m_timeSinceLast < m_spawnInterval)
        return {};

    m_timeSinceLast = 0.f;

    float spawnX = viewRight + GameConstants::GIFT_SPAWN_OFFSET_X;
    float spawnY = GameConstants::GIFT_BASE_Y + 
                   (rand() % static_cast<int>(GameConstants::GIFT_Y_RANDOM_RANGE));


    std::vector<std::unique_ptr<StaticObject>> gifts;

    auto gift = GameFactory<StaticObject, GiftType>::create("Gift", std::move(type));
    if (!gift)
        throw std::runtime_error("GiftSpawner failed to create Gift object");

    gift->setPosition({ spawnX, spawnY });

    gifts.push_back(std::move(gift));

    m_spawnInterval = GameConstants::GIFT_SPAWN_INTERVAL_MIN +
                      static_cast<float>(rand() % GameConstants::GIFT_SPAWN_INTERVAL_RANGE);


    return gifts;
}
