#pragma once
#include "Objects/GameObject.h"
#include "Utils/ObjectType.h"

class StaticObject : public GameObject {
public:
    virtual void update(float dt) override;
};
