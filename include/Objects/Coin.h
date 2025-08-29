#pragma once
#include "StaticObject.h"
#include "AnimationComponent.h"

class Coin : public StaticObject {
public:
    Coin();
    void update(float dt) override;
    void setCollected() {
            markForDeletion();
    }

private:
    AnimationComponent m_animation;
};
