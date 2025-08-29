#include "Spawners/LaserSpawner.h"
#include "factory/GameFactory.h"
#include "Objects/Laser.h"
#include "Utils/GameConstants.h"

bool registerLaserSpawner = GameFactory<StaticObjectSpawner>::registerit(
    "LaserSpawner", []() -> std::unique_ptr<StaticObjectSpawner> {
        return std::make_unique<LaserSpawner>();
    }
);

float LaserSpawner::getRandomSpawnInterval() {
    return GameConstants::LASER_SPAWN_INTERVAL_MIN +
        static_cast<float>(rand() % GameConstants::LASER_SPAWN_INTERVAL_VARIATION) / 100.f;

}
LaserSpawner::LaserSpawner() = default;

std::vector<std::unique_ptr<StaticObject>> LaserSpawner::update(float dt, float viewRight) {

    if (viewRight - m_lastSpawnX < m_minDistance)
        return {};

    m_lastSpawnX = viewRight;

    std::vector<std::unique_ptr<StaticObject>> lasers;
    auto laser = GameFactory<StaticObject>::create("Laser");
    if (!laser)
        throw std::runtime_error("LaserSpawner failed to create Laser object");

    float scale = GameConstants::LASER_SCALE;
    laser->setScale(scale, scale);



    int rotationOption = rand() % 2;
    float rotation = (rotationOption == 0) ? GameConstants::LASER_ROTATION_HORIZONTAL
        : GameConstants::LASER_ROTATION_VERTICAL;
    laser->setRotation(rotation);


    sf::FloatRect bounds = laser->getSprite().getLocalBounds();
    float laserWidth = bounds.width * scale;
    float laserHeight = bounds.height * scale;

    float screenTop = GameConstants::LASER_VERTICAL_SCREEN_MARGIN;
    float screenBottom = GameConstants::SCREEN_HEIGHT - GameConstants::LASER_VERTICAL_SCREEN_MARGIN;

    float posY;
    if (rotation == GameConstants::LASER_ROTATION_HORIZONTAL) {
        posY = screenTop + static_cast<float>(rand()) / 
               RAND_MAX * (screenBottom - screenTop - laserHeight);
    }
    else {
        posY = screenTop + static_cast<float>(rand()) / 
               RAND_MAX * (screenBottom - screenTop - laserWidth);
    }


    float posX = viewRight + GameConstants::LASER_SPAWN_OFFSET_X;

    laser->setPosition({ posX, posY });

    lasers.push_back(std::move(laser));
    return lasers;
        return lasers;
}
