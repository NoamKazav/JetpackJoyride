#include "CoinPatterns/HorizontalLinePattern.h"

bool HorizontalLinePattern::m_registerit = GameFactory<CoinPattern, int&, float&>::registerit(
    "HorizontalLinePattern", [](int& a, float& b) -> std::unique_ptr<CoinPattern> {
        return std::make_unique<HorizontalLinePattern>(a, b);
    });

std::vector<std::unique_ptr<StaticObject>> HorizontalLinePattern::generate(float startX, float startY)  {
    std::vector<std::unique_ptr<StaticObject>> coins;
    for (int i = 0; i < m_num; ++i) {
        auto coin = GameFactory<StaticObject>::create("Coin");
        if (coin)
            coin->setPosition({ startX + i * m_spacing, startY });
        coins.push_back(std::move(coin));
    }
    return coins;
}