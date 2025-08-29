#include "state/TankWalkingState.h"
#include "factory/GameFactory.h"

bool TankWalkingState::m_registerit = GameFactory<PlayerState>::registerit(
    "TankWalking",
    []() -> std::unique_ptr<PlayerState> {
        return std::make_unique<TankWalkingState>();
    }
);

std::unique_ptr<PlayerState> TankWalkingState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        return GameFactory<PlayerState>::create("TankJetting");
    return nullptr;
}

std::unique_ptr<PlayerState> TankWalkingState::update(Player&, float) {
    return nullptr;
}
std::string TankWalkingState::getAnimationName() const {
    return "walking tank";
}
