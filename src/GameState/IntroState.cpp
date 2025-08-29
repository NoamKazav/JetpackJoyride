#include "GameStates/IntroState.h"
#include "GameStates/PlayingState.h"
#include "GameCore/Resources.h"
#include "Utils/GameConstants.h"
#include "GameCore/Controller.h"
#include <stdexcept>
#include "factory/GameFactory.h"

bool IntroState::m_registerit = GameFactory<GameState>::registerit("IntroState",
    []() -> std::unique_ptr<GameState> {
        return std::make_unique<IntroState>();
    });


IntroState::IntroState() {
    m_frames = Resources::getInstance().getAnimationFrames("Intro");
    if (!m_frames || m_frames->empty())
        throw std::runtime_error("Missing animation frames for 'Intro'");

    m_sprite.setTexture(Resources::getInstance().getObjectTexture(ObjectType::Intro));
    if (m_frames->empty())
        throw std::runtime_error("Animation frames for 'Intro' are empty");

    m_sprite.setTextureRect((*m_frames)[0]);

    if ((*m_frames)[0].width == 0 || (*m_frames)[0].height == 0)
        throw std::runtime_error("Invalid frame dimensions for 'Intro' animation");

    float scaleX = static_cast<float>(GameConstants::SCREEN_WIDTH) / (*m_frames)[0].width;
    float scaleY = static_cast<float>(GameConstants::SCREEN_HEIGHT) / (*m_frames)[0].height;
    m_sprite.setScale(scaleX, scaleY);
    m_sprite.setPosition(0.f, 0.f);
}

void IntroState::enter(Controller& controller)
{
    Resources::getInstance().playSound(SoundType::Explosion);
}

std::unique_ptr<GameState> IntroState::handleInput(const sf::Event& event) {
    return nullptr;
}

std::unique_ptr<GameState> IntroState::update(float dt, Controller& controller) {
    m_elapsed += dt;
    m_timeSinceLastFrame += dt;

    if (m_timeSinceLastFrame >= m_frameTime) {
        m_timeSinceLastFrame = 0.f;
        m_currentFrame = (m_currentFrame + 1) % m_frames->size();
        m_sprite.setTextureRect((*m_frames)[m_currentFrame]);
    }

    if (m_elapsed > GameConstants::INTRO_DURATION) {
        auto next = std::make_unique<PlayingState>(controller.getWindow());
        if (!next)
            throw std::runtime_error("Failed to create PlayingState from IntroState");
        return next;
    }

    return nullptr;
}

void IntroState::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}
