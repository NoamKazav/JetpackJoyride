#include "Objects/Player.h"
#include "state/WalkingState.h"
#include "state/DeadState.h"
#include "GameCore/Resources.h"
#include "Utils/ObjectType.h"
#include "factory/GameFactory.h"
#include <iostream>
#include <stdexcept> 
#include "Utils/GameConstants.h"

bool Player::m_registerit = GameFactory<GameObject>::registerit("Player", []() -> std::unique_ptr<GameObject> {
    return (std::make_unique<Player>());
    });

Player::Player() {
    const auto& tex = Resources::getInstance().getObjectTexture(ObjectType::Player);
    setTexture(&tex);
    auto* frames = Resources::getInstance().getAnimationFrames("walking berry");
    if (!frames || frames->empty())
        throw std::runtime_error("Missing animation frames for 'walking berry'");
    setTextureRect((*frames)[0]);
    setPosition({ GameConstants::PLAYER_INITIAL_X - (*frames)[0].width / 2.f,
                  GameConstants::PLAYER_INITIAL_Y });

    m_animation.setFrames(frames);
    setState(GameFactory<PlayerState>::create("Walking"));
}

void Player::handleEvents(const sf::Event& event) {
    if (m_state) {
        if (auto next = m_state->handleInput(event))
            setState(std::move(next));
    }
}

void Player::update(float dt) {
    if (m_state) {
        if (auto next = m_state->update(*this, dt))
            setState(std::move(next));
    }
    m_animation.update(dt, *this);

    if (m_invincibleTime > 0.f)
        m_invincibleTime -= dt;
    for (auto it = m_activeEffects.begin(); it != m_activeEffects.end(); ) {
        it->timeRemaining -= dt;
        if (it->timeRemaining <= 0.f)
            it = m_activeEffects.erase(it);
        else
            ++it;
    }
}

void Player::render(sf::RenderWindow& window) const {
    GameObject::render(window);
    if (m_state)
        m_state->renderExtras(*this, window);

}

void Player::setState(std::unique_ptr<PlayerState> newState) {
    if (!newState)
        throw std::runtime_error("Attempted to set null player state");

    float oldBottom = getBottom();

    m_state = std::move(newState);
    m_state->enter(*this);

    float newBottom = getBottom();
    float dy = oldBottom - newBottom;
    move(0.f, dy);
}

void Player::setAnimation(const std::string& animationName)
{
    const auto* frames = Resources::getInstance().getAnimationFrames(animationName);
    if (!frames || frames->empty())
        throw std::runtime_error("Missing animation frames for '" + animationName + "'");

    if (animationName == "Dead")
        setTexture(&Resources::getInstance().getObjectTexture(ObjectType::Dead));
    else if (animationName.find("tank") != std::string::npos && animationName.find("jumping") != std::string::npos) {
        setTexture(&Resources::getInstance().getObjectTexture(ObjectType::JetTank));
    }
    else if (animationName.find("tank") != std::string::npos) {
        setTexture(&Resources::getInstance().getObjectTexture(ObjectType::Tank));
    }
    else if (animationName.find("Gravity") != std::string::npos) {
        setTexture(&Resources::getInstance().getObjectTexture(ObjectType::Gravity));
    }
    else
        setTexture(&Resources::getInstance().getObjectTexture(ObjectType::Player));

    setTextureRect((*frames)[0]);
    m_animation.setFrames(frames);
}

void Player::setTextureRect(const sf::IntRect& rect) {
    GameObject::setTextureRect(rect);
}

void Player::anchorToViewLeft(float viewLeftX) {
    setPosition({ viewLeftX + GameConstants::PLAYER_ANCHOR_LEFT_OFFSET, getPosition().y });
}

void Player::clampToGround(float groundY) {
    auto x = getSprite().getPosition().x;
    setPosition({ x, groundY });
}

void Player::clampBottomToGround(float groundY)
{
    float spriteHeight = static_cast<float>(getSprite().getTextureRect().height);
    float newY = groundY - spriteHeight;
    float x = getPosition().x;
    setPosition({ x, newY });
}

void Player::move(float dx, float dy) {
    setPosition({ getPosition().x + dx, getPosition().y + dy });
}

void Player::trackOrRefreshEffect(std::shared_ptr<GiftEffect> effect, float duration)
{
    for (auto& active : m_activeEffects) {
        if (active.effect == effect) {
            active.timeRemaining = duration;
            return;
        }
    }
    m_activeEffects.push_back({ effect, duration });
}

bool Player::isGameOverRequested() const {
    return m_gameOverRequested;
}

void Player::requestGameOver() {
    m_gameOverRequested = true;
}

float Player::getBottom() const {
    return getPosition().y + getSprite().getGlobalBounds().height;
}

bool Player::isDead() const
{
    return dynamic_cast<const DeadState*>(m_state.get()) != nullptr;
}

AnimationComponent& Player::getAnimation()
{
    return m_animation;
}

const AnimationComponent& Player::getAnimation() const
{
    return m_animation;
}

void Player::collectCoin() {
    ++m_collectedCoins;
}

int Player::getCollectedCoins() const {
    return m_collectedCoins;
}

bool Player::hasActiveEffect() const {
    return !m_activeEffects.empty();
}

void Player::clearAllEffects() {
    m_activeEffects.clear();
}

bool Player::isInvincible() const {
    return m_invincibleTime > 0.f;
}

void Player::setInvincibleFor(float seconds) {
    m_invincibleTime = seconds;
}
