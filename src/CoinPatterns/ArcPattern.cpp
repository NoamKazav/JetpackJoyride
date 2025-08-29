#include "CoinPatterns/ArcPattern.h"
#include "factory/GameFactory.h"
#include "Utils/GameConstants.h"
#include <cmath>
#include <stdexcept>

ArcPattern::ArcPattern(int coinsPerLayer, int layers, float radius)
    : m_coinsPerLayer(coinsPerLayer), m_layers(layers), m_radius(radius) {}

std::vector<std::unique_ptr<StaticObject>> ArcPattern::generate(float startX, float startY) {
    if (m_coinsPerLayer < GameConstants::ARC_PATTERN_MIN_COINS_PER_LAYER)
        throw std::invalid_argument("ArcPattern: coinsPerLayer must be at least 2");
    if (m_layers <= 0)
        throw std::invalid_argument("ArcPattern: layers must be positive");
    if (m_radius <= 0.f)
        throw std::invalid_argument("ArcPattern: radius must be positive");

    std::vector<std::unique_ptr<StaticObject>> coins;

    float totalAngle = GameConstants::ARC_PATTERN_TOTAL_ANGLE;
    float angleStep = totalAngle / (m_coinsPerLayer - 1);
    float baseAngle = -totalAngle / 2.f;

    for (int layer = 0; layer < m_layers; ++layer) {
        float layerRadius = m_radius + layer * GameConstants::ARC_PATTERN_LAYER_RADIUS_STEP;

        for (int i = 0; i < m_coinsPerLayer; ++i) {
            float angle = baseAngle + i * angleStep;

            float x = startX + layerRadius * std::sin(angle);
            float y = startY - layerRadius * std::cos(angle) + layer * GameConstants::ARC_PATTERN_LAYER_HEIGHT_STEP;

            auto coin = GameFactory<StaticObject>::create("Coin");
            if (!coin)
                throw std::runtime_error("ArcPattern: failed to create coin from factory");

            coin->setPosition({ x, y });
            coins.push_back(std::move(coin));
        }
    }

    return coins;
}
