#pragma once
#include "Spawners/MovingObjectSpawner.h"
#include "Objects/Player.h"
#include "Objects/Missile.h"

class MissileSpawner : public MovingObjectSpawner {
public:
    MissileSpawner(Player& player) : m_player(player) {}

    std::vector<std::unique_ptr<MovingObject>> update(float dt, float viewRight) override;

private:
    Player& m_player;
    float m_spawnCooldown = 20.0f;
    float m_timeSinceLastSpawn = 0.0f;
};
