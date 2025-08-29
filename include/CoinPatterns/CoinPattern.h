#pragma once
#include <vector>
#include <memory>
#include "Objects/GameObject.h"
#include <numbers>
#include "Objects/StaticObject.h"
class CoinPattern {
public:
    virtual ~CoinPattern() = default;
    virtual std::vector<std::unique_ptr<StaticObject>> generate(float startX, float startY) = 0;
};