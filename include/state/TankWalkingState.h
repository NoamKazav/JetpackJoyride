#pragma once
#include "state/CommonWalkingState.h"
#include "Objects/Player.h"

class TankWalkingState : public CommonWalkingState {
public:
    static bool m_registerit;
    std::unique_ptr<PlayerState> handleInput(const sf::Event&) override;
    std::unique_ptr<PlayerState> update(Player& player, float dt) override;
    std::string getAnimationName() const override;
};
