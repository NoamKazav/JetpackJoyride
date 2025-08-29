#pragma once
#include <vector>
#include <memory>
#include "Objects/StaticObject.h"

class LaserPattern {
public:
    virtual ~LaserPattern() = default;

    virtual std::vector<std::unique_ptr<StaticObject>> generate(float startX, float startY) const = 0;
};
