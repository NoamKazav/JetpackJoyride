#include "GameStates/LoadingState.h"
#include "GameStates/MenuState.h"
#include "GameCore/Controller.h"
#include "GameCore/Resources.h"
#include "Utils/GameConstants.h"
#include <stdexcept>
#include "factory/GameFactory.h"
bool LoadingState::m_registerit = GameFactory<GameState>::registerit("LoadingState",
    []() -> std::unique_ptr<GameState> {
        return std::make_unique<LoadingState>();
    });

LoadingState::LoadingState() {
    const auto& tex = Resources::getInstance().getBackgroundTexture("loading");
    if (tex.getSize().x == 0 || tex.getSize().y == 0)
        throw std::runtime_error("Failed to load loading background texture");

    m_sprite.setTexture(tex);

    float scaleX = GameConstants::SCREEN_WIDTH / static_cast<float>(tex.getSize().x);
    float scaleY = GameConstants::SCREEN_HEIGHT / static_cast<float>(tex.getSize().y);
    m_sprite.setScale(scaleX, scaleY);
    m_sprite.setPosition(0.f, 0.f);

    if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
        throw std::runtime_error("Could not load font");

    m_loadingText.setFont(m_font);
    m_loadingText.setCharacterSize(GameConstants::LOADING_TEXT_SIZE);
    m_loadingText.setFillColor(sf::Color::White);
    m_loadingText.setString("0%");

    sf::FloatRect bounds = m_loadingText.getLocalBounds();
    m_loadingText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    m_loadingText.setPosition(GameConstants::SCREEN_WIDTH / 2.f,
                              GameConstants::SCREEN_HEIGHT - GameConstants::LOADING_TEXT_Y_OFFSET);
}

std::unique_ptr<GameState> LoadingState::update(float dt, Controller& controller) {
    m_elapsed += dt;

    float percentage = std::min(GameConstants::PERCENTAGE_MAX,
                               (m_elapsed / m_loadingDuration) * GameConstants::PERCENTAGE_MAX);

    m_loadingText.setString(std::to_string(static_cast<int>(percentage)) + "%");

    sf::FloatRect bounds = m_loadingText.getLocalBounds();
    m_loadingText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    if (m_elapsed >= m_loadingDuration) {
        auto next = GameFactory<GameState>::create("MenuState");
        if (!next)
            throw std::runtime_error("Failed to create MenuState from LoadingState");
        return next;
    }

    return nullptr;
}

void LoadingState::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
    window.draw(m_loadingText);
}
