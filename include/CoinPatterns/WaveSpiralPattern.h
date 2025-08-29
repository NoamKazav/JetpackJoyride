#pragma once
#include "CoinPattern.h"
#include "factory/GameFactory.h"
#include <cmath>

class WaveSpiralPattern : public CoinPattern {
public:
    WaveSpiralPattern(int num, float spacingX, float waveHeight, float frequency)
        : m_num(num), m_spacingX(spacingX), m_waveHeight(waveHeight), m_frequency(frequency) {}

    std::vector<std::unique_ptr<StaticObject>> generate(float startX, float startY);

private:
    int m_num;
    float m_spacingX;
    float m_waveHeight;
    float m_frequency;
    static bool m_registerit;
};
