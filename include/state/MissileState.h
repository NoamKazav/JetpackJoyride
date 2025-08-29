#pragma once
class MissileSpawner;

class MissileState {
public:
    virtual ~MissileState() = default;
    virtual void update(float dt, MissileSpawner& spawner) = 0;
};