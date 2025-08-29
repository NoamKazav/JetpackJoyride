#pragma once
#include "Objects/Missile.h"

class MissileAnimationState {
public:
    virtual ~MissileAnimationState() = default;
    virtual void update(Missile* missile, float dt, float scrollSpeed) = 0;
};