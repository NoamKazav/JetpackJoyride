#include "Spawners/CoinSpawner.h"
#include "factory/GameFactory.h"
#include <stdexcept> 
#include "Utils/GameConstants.h"

bool CoinSpawner::m_registerit = GameFactory<StaticObjectSpawner>::registerit(
    "CoinSpawner",
    []() -> std::unique_ptr<StaticObjectSpawner> {
        return std::make_unique<CoinSpawner>();
    }
);

std::vector<std::unique_ptr<StaticObject>> CoinSpawner::update(float dt, float viewRight) {
    if (viewRight - m_lastSpawnX < m_minDistance)
        return {};

    m_lastSpawnX = viewRight;

    float spawnX = viewRight + GameConstants::COIN_SPAWN_OFFSET_X;
    float spawnY = GameConstants::COIN_BASE_Y + (rand() % 200 - GameConstants::COIN_Y_RANDOM_RANGE);

    std::vector<std::unique_ptr<StaticObject>> coins;
    int randVal = rand() % 5;

    switch (randVal) {
    case 0:
        coins = HorizontalLinePattern(
            GameConstants::COIN_LINE_COUNT_MIN + rand() % GameConstants::COIN_LINE_COUNT_VARIATION,
            GameConstants::COIN_LINE_SPACING
        ).generate(spawnX, spawnY);
        break;
    case 1:
        coins = ArcPattern(GameConstants::ARC_PATTERN_NUM_COINS,
            GameConstants::ARC_PATTERN_NUM_LAYERS,
            GameConstants::ARC_PATTERN_RADIUS)
            .generate(spawnX, spawnY + GameConstants::ARC_PATTERN_Y_OFFSET);
        break;
    case 2:
        coins = CirclePattern(GameConstants::CIRCLE_PATTERN_NUM_COINS,
            GameConstants::CIRCLE_PATTERN_RADIUS)
            .generate(spawnX + GameConstants::CIRCLE_PATTERN_X_OFFSET, spawnY);
        break;
    case 3:
        coins = WaveSpiralPattern(GameConstants::WAVE_PATTERN_NUM_COINS,
            GameConstants::WAVE_PATTERN_AMPLITUDE,
            GameConstants::WAVE_PATTERN_WAVELENGTH,
            GameConstants::WAVE_PATTERN_SPIRAL_FACTOR)
            .generate(spawnX, spawnY);
        break;
    case 4: {
        HorizontalLinePattern line(
            GameConstants::COIN_LINE_COUNT_MIN + 1,  
            GameConstants::COIN_DOUBLE_ROW_SPACING
        );
        auto row1 = line.generate(spawnX, spawnY);
        auto row2 = line.generate(spawnX, spawnY + GameConstants::COIN_DOUBLE_ROW_SPACING);
        coins.insert(coins.end(),
            std::make_move_iterator(row1.begin()),
            std::make_move_iterator(row1.end()));
        coins.insert(coins.end(),
            std::make_move_iterator(row2.begin()),
            std::make_move_iterator(row2.end()));
        break;
    }
    default:
        throw std::runtime_error("Unexpected random value in CoinSpawner::update");
    }

    return coins;
}
