#include "state/JettingState.h"
#include "state/FallingState.h"
#include "GameCore/Resources.h"
#include "Objects/Player.h"
#include "factory/GameFactory.h"
#include "Utils/GameConstants.h"

bool JettingState::m_registerit = GameFactory<PlayerState>::registerit(
    "Jetting",
    []() -> std::unique_ptr<PlayerState> {
        return std::make_unique<JettingState>();
    }
);
std::unique_ptr<PlayerState> JettingState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
        return GameFactory<PlayerState>::create("Falling");
    return nullptr;
}

std::unique_ptr<PlayerState> JettingState::update(Player& player, float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player.setVelocityY(GameConstants::JETTING_UPWARD_SPEED);
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

void JettingState::renderExtras(const Player& player, sf::RenderWindow& window) {
    auto frames = Resources::getInstance().getAnimationFrames("Exhaust");
    if (!frames || frames->empty()) return;

    static size_t flameFrame = 0;
    static sf::Clock flameClock;

    if (flameClock.getElapsedTime().asSeconds() > 0.1f) {
        flameFrame = (flameFrame + 1) % frames->size();
        flameClock.restart();
    }

    sf::Sprite flame;
    flame.setTexture(Resources::getInstance().getObjectTexture(ObjectType::Exhaust));
    flame.setTextureRect((*frames)[flameFrame]);

    auto pos = player.getSprite().getPosition();
    flame.setPosition(pos.x + GameConstants::JET_FLAME_OFFSET_X,
        pos.y + GameConstants::JET_FLAME_OFFSET_Y);
    window.draw(flame);
    drawShieldIfNeeded(player, window);
}

std::string JettingState::getAnimationName() const {
    return "jumping berry";
}
