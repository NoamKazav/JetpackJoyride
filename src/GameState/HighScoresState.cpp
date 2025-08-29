#include "GameStates/HighScoresState.h"
#include "GameCore/Resources.h"
#include "GameCore/Controller.h"
#include "GameStates/MenuState.h"
#include <sstream>
#include <stdexcept>

bool HighScoresState::m_registerit = GameFactory<GameState>::registerit("HighScoresState",
    []() -> std::unique_ptr<GameState> {
        return std::make_unique<HighScoresState>();
    });

void HighScoresState::enter(Controller& controller) {
    m_controller = &controller;


    m_background.setTexture(Resources::getInstance().getBackgroundTexture("menu"));
    const sf::Texture* tex = m_background.getTexture();
    if (!tex)
        throw std::runtime_error("Failed to load background texture for HighScoresState");

    m_background.setScale(
        GameConstants::SCREEN_WIDTH / tex->getSize().x,
        GameConstants::SCREEN_HEIGHT / tex->getSize().y
    );

    if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        m_font = Resources::getInstance().getFont();  // כבר זורק חריגה אם נכשל
    }

    auto scores = Resources::getInstance().getBestScores();
    m_scoreTexts.clear();
    float y = GameConstants::SCORES_START_Y;

    for (size_t i = 0; i < scores.size(); ++i) {
        sf::Text text;
        std::stringstream ss;
        ss << i + 1 << ". " << scores[i].first << " - " << static_cast<int>(scores[i].second) << " m";
        text.setFont(m_font);
        text.setString(ss.str());
        text.setCharacterSize(GameConstants::SCORES_TEXT_SIZE);
        text.setFillColor(sf::Color::White);
        text.setPosition(GameConstants::SCORES_TEXT_X, y);
        y += GameConstants::SCORES_LINE_SPACING;
        m_scoreTexts.push_back(text);
    }

    m_backButton.setTexture(Resources::getInstance().getButtonTexture("backToMenu"));
    m_backButton.setScale(GameConstants::DEFAULT_BUTTON_SCALE, GameConstants::DEFAULT_BUTTON_SCALE);
    m_backButton.setPosition(
        GameConstants::SCREEN_WIDTH - m_backButton.getGlobalBounds().width - 
        GameConstants::SCORES_BUTTON_MARGIN,
        GameConstants::SCORES_BUTTON_MARGIN);
    m_backButtonBounds = m_backButton.getGlobalBounds();
}

std::unique_ptr<GameState> HighScoresState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f clickPos(event.mouseButton.x, event.mouseButton.y);
        if (m_backButtonBounds.contains(clickPos)) {
            auto menu = GameFactory<GameState>::create("MenuState");
            if (!menu)
                throw std::runtime_error("Failed to create MenuState from HighScoresState");
            return menu;
        }
    }
    return nullptr;
}

std::unique_ptr<GameState> HighScoresState::update(float, Controller&) {
    return nullptr;
}

void HighScoresState::render(sf::RenderWindow& window) {
    window.draw(m_background);
    for (const auto& text : m_scoreTexts)
        window.draw(text);
    window.draw(m_backButton);
}
