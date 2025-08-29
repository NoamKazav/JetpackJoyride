#pragma once
#include "Spawners/StaticObjectSpawner.h"
#include "CoinPatterns/CoinPattern.h"
#include "CoinPatterns/HorizontalLinePattern.h"
#include "CoinPatterns/ArcPattern.h"
#include "CoinPatterns/CirclePattern.h"
#include "CoinPatterns/WaveSpiralPattern.h"
#include "Utils/GameConstants.h"

class CoinSpawner : public StaticObjectSpawner {
public:
    std::vector<std::unique_ptr<StaticObject>> update(float dt, float viewRight) override;

private:
    float m_lastSpawnX = 0.f;
    const float m_minDistance = GameConstants::COIN_DISTANCE;
    static bool m_registerit;
};
