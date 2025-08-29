#include "state/FallingState.h"
#include "state/WalkingState.h"
#include "factory/GameFactory.h"
#include "Utils/GameConstants.h"

bool FallingState::m_registerit = GameFactory<PlayerState>::registerit(
    "Falling",
    []() -> std::unique_ptr<PlayerState> {
        return std::make_unique<FallingState>();
    }
);

std::unique_ptr<PlayerState> FallingState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        return GameFactory<PlayerState>::create("Jetting");
    return nullptr;
}

std::unique_ptr<PlayerState> FallingState::update(Player& player, float dt) {
    player.move(0, GameConstants::FALLING_SPEED * dt);
    if (player.getSprite().getPosition().y >= GameConstants::PLAYER_INITIAL_Y) {
        player.clampToGround(450.f);
        return GameFactory<PlayerState>::create("Walking");
    }
    return nullptr;
}

std::string FallingState::getAnimationName() const {
    return "jumping berry";
}
