#pragma once
#include "state/PlayerState.h"
#include "state/CommonFallingState.h"

class FallingState : public CommonFallingState {
public:
    static bool m_registerit;
    std::unique_ptr<PlayerState> handleInput(const sf::Event&) override;
    std::unique_ptr<PlayerState> update(Player& player, float dt) override;
    void renderExtras(const Player& player, sf::RenderWindow& window) {
        drawShieldIfNeeded(player, window);
    }
    std::string getAnimationName() const override;
};
