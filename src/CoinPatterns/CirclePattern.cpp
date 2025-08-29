#include "CoinPatterns/CirclePattern.h"
#include "Utils/GameConstants.h"


bool CirclePattern::m_registerit = GameFactory<CoinPattern,int&, float&>::registerit(
    "CirclePattern", [](int &a, float &b) -> std::unique_ptr<CoinPattern> {
        return std::make_unique<CirclePattern>(a, b);
    });

std::vector<std::unique_ptr<StaticObject>> CirclePattern::generate(float centerX, float centerY)  {
    std::vector<std::unique_ptr<StaticObject>> coins;
    for (int i = 0; i < m_num; ++i) {
        float angle = GameConstants::TWO_PI * i / m_num;
        float x = centerX + std::cos(angle) * m_radius;
        float y = centerY + std::sin(angle) * m_radius;

        auto coin = GameFactory<StaticObject>::create("Coin");
        if (coin) {
            coin->setPosition({ x, y });
            coins.push_back(std::move(coin));
        }
    }
    return coins;
}