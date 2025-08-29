#include "Spawners/MissileSpawner.h"
#include "factory/GameFactory.h"
#include "Objects/Missile.h"
#include "Utils/GameConstants.h"
#include <iostream>

bool registerMissileSpawner = GameFactory<MovingObjectSpawner, Player&>::registerit(
    "MissileSpawner", [](Player& p) -> std::unique_ptr<MovingObjectSpawner> {
        return std::make_unique<MissileSpawner>(p); 
    }
);

std::vector<std::unique_ptr<MovingObject>> MissileSpawner::update(float dt, float viewRight)
{
    m_timeSinceLastSpawn += dt;

    std::vector<std::unique_ptr<MovingObject>> output;

    if (m_timeSinceLastSpawn >= m_spawnCooldown) {
        m_timeSinceLastSpawn = 0.f;

        auto missile = std::make_unique<Missile>();

        missile->setPlayerRef(&m_player);
        missile->setWarningPosition(viewRight, m_player.getPosition().y);
        output.push_back(std::move(missile));
    }

    return output;
}
