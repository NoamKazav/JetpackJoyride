#pragma once
#include "state/MissileAnimationState.h"

class AlertMissileState : public MissileAnimationState {
public:
    AlertMissileState(Missile* missile);
    void update(Missile* missile, float dt, float scrollSpeed);

private:
    float m_timer = 0.f;
    bool m_firstTime = true;
    bool m_followY = true;
    static bool m_registerit;
};