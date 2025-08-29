#pragma once

#include "PlayerState.h"
#include <SFML/System/Clock.hpp>

class DeadState : public PlayerState {
public:
    DeadState();

    void enter(Player& player) override;
    std::unique_ptr<PlayerState> handleInput(const sf::Event& event) override;
    std::unique_ptr<PlayerState> update(Player& player, float dt) override;

private:

    float m_timeAccumulator = 0.f;
    static bool m_registerit;
};
