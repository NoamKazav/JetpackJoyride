#include "state/DeadState.h"
#include "Objects/Player.h"
#include "GameCore/Resources.h"
#include "Utils/GameConstants.h"
#include "factory/GameFactory.h"

bool DeadState::m_registerit = GameFactory<PlayerState>::registerit(
    "Dead",
    []() -> std::unique_ptr<PlayerState> {
        return std::make_unique<DeadState>();
    }
);
DeadState::DeadState()
{}

void DeadState::enter(Player& player) {
    player.setVelocityY(0.f);
    player.setAnimation("Dead");
    player.getAnimation().setPlayOnce(true);
}

std::unique_ptr<PlayerState> DeadState::update(Player& player, float dt) {
    player.increaseVelocityY(GameConstants::GRAVITY * dt);
    player.move(0.f, player.getVelocityY() * dt);

    const float groundY = static_cast<float>(GameConstants::DEFAULT_START_POINT);
    if (player.getBottom() >= groundY) {
        player.clampBottomToGround(groundY);
        player.setVelocityY(0.f);
    }

    if (player.getAnimation().isFinished()) {
        m_timeAccumulator += dt;
        if (m_timeAccumulator >= GameConstants::DEAD_STATE_GAME_OVER_DELAY) {
            player.requestGameOver();
        }
    }

    return nullptr;
}

std::unique_ptr<PlayerState> DeadState::handleInput(const sf::Event&) {
    return nullptr; 
}




