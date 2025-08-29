#include "CoinPatterns/WaveSpiralPattern.h"

bool WaveSpiralPattern::m_registerit = GameFactory<CoinPattern, int&, float&, float&, float&>::registerit(
    "WaveSpiralPattern", [](int& a, float& b, float&c, float& d) -> std::unique_ptr<CoinPattern> {
        return std::make_unique<WaveSpiralPattern>(a, b,c,d);
    });

std::vector<std::unique_ptr<StaticObject>> WaveSpiralPattern::generate(float startX, float startY)  {
    std::vector<std::unique_ptr<StaticObject>> coins;

    for (int i = 0; i < m_num; ++i) {
        float x = startX + i * m_spacingX;
        float angle = i * m_frequency;
        float y = startY + std::sin(angle) * m_waveHeight;

        auto coin = GameFactory<StaticObject>::create("Coin");
        if (coin) {
            coin->setPosition({ x, y });
            coins.push_back(std::move(coin));
        }
    }

    return coins;
}