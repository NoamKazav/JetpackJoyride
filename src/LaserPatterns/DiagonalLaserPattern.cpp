#include "LaserPatterns/DiagonalLaserPattern.h"
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include "Utils/GameConstants.h"
#include "factory/GameFactory.h"
bool DiagonalLaserPattern::m_registerit = GameFactory<LaserPattern>::registerit(
    "DiagonalLaserPattern", []() -> std::unique_ptr<LaserPattern> {
        return std::make_unique<DiagonalLaserPattern>();
    });

std::vector<std::unique_ptr<StaticObject>> DiagonalLaserPattern::generate(float startX, float startY) const {
    std::vector<std::unique_ptr<StaticObject>> lasers;


    std::default_random_engine rng(static_cast<unsigned>(time(nullptr)));
    std::uniform_real_distribution<float> angleDist(GameConstants::MINANGLE, GameConstants::MAXANGLE);

    for (int i = 0; i < GameConstants::NUMLASERS; ++i) {
        float angle = angleDist(rng);

        if (angle < GameConstants::LASER_MIN_ROTATION || angle > GameConstants::LASER_MAX_ROTATION)
            throw std::out_of_range("Laser angle out of acceptable range");

        float x = startX + i * GameConstants::STEP;
        float y = startY + std::tan(angle * GameConstants::DEG_TO_RAD) * (i * GameConstants::STEP);

        auto laser = GameFactory<StaticObject>::create("Laser");
        if (!laser)
            throw std::runtime_error("Failed to allocate Laser");

        laser->setPosition({ x, y });
        laser->setRotation(angle);
        lasers.push_back(std::move(laser));
    }

    return lasers;
}
