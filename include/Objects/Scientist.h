#pragma once

#include "MovingObject.h"
#include "AnimationComponent.h"
#include "Utils/GameConstants.h"

class Scientist : public MovingObject {
public:
    Scientist();

    void update(float dt) override;
    void move(float dx, float dy) override;

private:
    AnimationComponent m_animation;
    sf::Vector2f m_velocity = GameConstants::SCIENTIST_INITIAL_VELOCITY;
};
