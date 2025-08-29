#pragma once
#include "state/PlayerState.h"
#include "state/CommonWalkingState.h"

class WalkingState : public CommonWalkingState {
public:
    static bool m_registerit;
    std::unique_ptr<PlayerState> handleInput(const sf::Event&) override;
    std::unique_ptr<PlayerState> update(Player& player, float dt) override;
    std::string getAnimationName() const override;
    void renderExtras(const Player& player, sf::RenderWindow& window) {
        drawShieldIfNeeded(player, window);
    }
};
