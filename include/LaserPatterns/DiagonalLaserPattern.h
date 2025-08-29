#pragma once
#include "LaserPatterns/LaserPattern.h"
#include "Objects/Laser.h"
#include <vector>
#include <memory>

class DiagonalLaserPattern : public LaserPattern {
public:
    DiagonalLaserPattern() = default;
    std::vector<std::unique_ptr<StaticObject>> generate(float startX, float viewRight) const override;

private:
    static bool m_registerit;
};
