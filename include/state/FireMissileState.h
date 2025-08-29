#pragma once
#include "state/MissileAnimationState.h"

class FireMissileState : public MissileAnimationState {
public:
    FireMissileState(Missile* missile);
    void update(Missile* missile, float dt, float scrollSpeed);

private:
    float m_timer = 0.f;
    static bool m_registerit;
};