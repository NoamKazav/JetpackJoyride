#pragma once
#include "state/CommonJettingState.h"
#include "Objects/Player.h"

class TankJettingState : public CommonJettingState {
public:
    static bool m_registerit;
    std::unique_ptr<PlayerState> handleInput(const sf::Event&) override;
    std::unique_ptr<PlayerState> update(Player& player, float dt) override;
    std::string getAnimationName() const override;
};
