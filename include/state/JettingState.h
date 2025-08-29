#pragma once
#include "state/PlayerState.h"
#include "state/CommonJettingState.h"

class JettingState : public CommonJettingState {
public:
    static bool m_registerit;
    std::unique_ptr<PlayerState> handleInput(const sf::Event&) override;
    std::unique_ptr<PlayerState> update(Player& player, float dt) override;
    void renderExtras(const Player& player, sf::RenderWindow& window) override;
    std::string getAnimationName() const override;
};
