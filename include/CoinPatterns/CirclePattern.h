#pragma once
#include "CoinPattern.h"
#include "factory/GameFactory.h"
#include <cmath>

class CirclePattern : public CoinPattern {
public:
    CirclePattern(int num, float radius)
        : m_num(num), m_radius(radius) {}

    std::vector<std::unique_ptr<StaticObject>> generate(float centerX, float centerY) override;

private:
    int m_num;
    float m_radius;
    static bool m_registerit;
};
