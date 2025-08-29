#include "state/TankJettingState.h"
#include "factory/GameFactory.h"
#include "Utils/GameConstants.h"

bool TankJettingState::m_registerit = GameFactory<PlayerState>::registerit(
    "TankJetting",
    []() -> std::unique_ptr<PlayerState> {
        return std::make_unique<TankJettingState>();
    }
);

std::unique_ptr<PlayerState> TankJettingState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
        return GameFactory<PlayerState>::create("TankFalling");
    return nullptr;
}

std::unique_ptr<PlayerState> TankJettingState::update(Player& player, float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player.setVelocityY(GameConstants::JETTING_UPWARD_SPEED);
    }
    else {
        return GameFactory<PlayerState>::create("TankFalling");
    }
    float dy = player.getVelocityY() * dt;
    auto pos = player.getSprite().getPosition();
    if (pos.y + dy < GameConstants::PLAYER_MIN_Y) {
        player.setPosition({ pos.x, GameConstants::PLAYER_MIN_Y });
        return nullptr;
    }
    player.move(0, dy);
    return nullptr;
}

std::string TankJettingState::getAnimationName() const {
    return "jumping tank";
}
