#pragma once
#include "ObjectSpawner.h"
#include "Objects/MovingObject.h"
#include <vector>
#include <memory>

class MovingObjectSpawner : public ObjectSpawner {
public:
    virtual std::vector<std::unique_ptr<MovingObject>> update(float dt, float viewRight) = 0;

};