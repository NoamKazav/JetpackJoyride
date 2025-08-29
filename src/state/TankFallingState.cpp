#include "state/TankFallingState.h"
#include "factory/GameFactory.h"
#include "Utils/GameConstants.h"

bool TankFallingState::m_registerit = GameFactory<PlayerState>::registerit(
    "TankFalling",
    []() -> std::unique_ptr<PlayerState> {
        return std::make_unique<TankFallingState>();
    }
);

std::unique_ptr<PlayerState> TankFallingState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        return GameFactory<PlayerState>::create("TankJetting");
    return nullptr;
}

std::unique_ptr<PlayerState> TankFallingState::update(Player& player, float dt) {
    player.move(0, GameConstants::FALLING_SPEED * dt);
    if (player.getSprite().getPosition().y >= GameConstants::PLAYER_INITIAL_Y) {
        player.clampToGround(GameConstants::PLAYER_INITIAL_Y);
        return GameFactory<PlayerState>::create("TankWalking");
    }
    return nullptr;
}

std::string TankFallingState::getAnimationName() const {
    return "jumping tank";
}
