#pragma once
#include "CoinPattern.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class ArcPattern : public CoinPattern {
public:
    ArcPattern(int coinsPerLayer, int layers, float radius);

    std::vector<std::unique_ptr<StaticObject>> generate(float startX, float startY);

private:
    int m_coinsPerLayer;
    float m_layers;
    float m_radius;
};
