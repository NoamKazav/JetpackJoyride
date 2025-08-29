#include "state/WalkingState.h"
#include "state/JettingState.h"
#include "factory/GameFactory.h"

bool WalkingState::m_registerit = GameFactory<PlayerState>::registerit(
    "Walking",
    []() -> std::unique_ptr<PlayerState> {
        return std::make_unique<WalkingState>();
    }
);

std::unique_ptr<PlayerState> WalkingState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        return GameFactory<PlayerState>::create("Jetting");
    return nullptr;
}

std::unique_ptr<PlayerState> WalkingState::update(Player&, float) {
    return nullptr;
}

std::string WalkingState::getAnimationName() const {
    return "walking berry";
}

