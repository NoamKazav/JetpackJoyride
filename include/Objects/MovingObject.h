#pragma once
#include "GameObject.h"

class MovingObject : public GameObject {
public:
    virtual void move(float dx, float dy) = 0; 
    virtual ~MovingObject() = default;
    virtual void update(float dt) override;

};