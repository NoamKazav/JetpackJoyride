#include "Objects/Missile.h"
#include "GameCore/Resources.h"
#include "state/AlertMissileState.h"
#include "Utils/ObjectType.h"
#include "Utils/GameConstants.h"
#include "Objects/Player.h"
#include "factory/GameFactory.h"

bool Missile::m_registerit = GameFactory<MovingObject>::registerit(
    "Missile", []() -> std::unique_ptr<MovingObject> {
        return std::make_unique<Missile>();
    }
);


Missile::Missile() {
    setState(GameFactory<MissileAnimationState, Missile&>::create("AlertMissileState", *this));
    
}

void Missile::update(float dt, float scrollSpeed) {
    if (m_state)
        m_state->update(this, dt, scrollSpeed);
}

void Missile::render(sf::RenderWindow& window) const {
    window.draw(getSprite());
}

void Missile::move(float dx, float dy) {
    sf::Vector2f currentPos = getPosition();
    setPosition({ currentPos.x + dx, currentPos.y + dy });
}

void Missile::setState(std::unique_ptr<MissileAnimationState> newState) {
    m_state = std::move(newState);
}

void Missile::setNewSprite(const std::string& animationName, ObjectType type) {
    const auto& tex = Resources::getInstance().getObjectTexture(type);
    setTexture(&tex);

    const auto* frames = Resources::getInstance().getAnimationFrames(animationName);
    if (!frames || frames->empty())
        throw std::runtime_error("Missing animation frames: " + animationName);

    setTextureRect((*frames)[0]);
    m_animation.setFrames(frames);
}

void Missile::animate(float dt) {
    m_animation.update(dt, *this);
}

void Missile::setPositionByPlayer() {
    float y = GameConstants::MISSILE_FIXED_Y;
    setPosition({ getPosition().x, y });
}
void Missile::setWarningPosition(float viewRight, float y) {
    setPosition({ viewRight - GameConstants::MISSILE_WARNING_OFFSET_X, y });
}

void Missile::setPlayerRef(Player* player)
{
    m_player = player;
}

float Missile::getPlayerY() const
{
    return m_player->getPosition().y;
}
