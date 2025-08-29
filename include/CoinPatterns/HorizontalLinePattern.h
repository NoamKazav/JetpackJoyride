#pragma once
#include "CoinPattern.h"
#include "factory/GameFactory.h"
#include <cmath>

class HorizontalLinePattern : public CoinPattern {
public:
    HorizontalLinePattern(int num, float spacing)
        : m_num(num), m_spacing(spacing) {}

    std::vector<std::unique_ptr<StaticObject>> generate(float startX, float startY);

private:
    int m_num;
    float m_spacing;
    static bool m_registerit;
};
