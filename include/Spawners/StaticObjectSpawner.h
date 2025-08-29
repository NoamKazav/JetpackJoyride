#pragma once
#include "Spawners/ObjectSpawner.h"

class StaticObjectSpawner : public ObjectSpawner {
public:
    virtual std::vector<std::unique_ptr<StaticObject>> update(float dt, float viewRight) = 0;
};