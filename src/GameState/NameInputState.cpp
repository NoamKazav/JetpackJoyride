#include "GameStates/NameInputState.h"
#include "GameCore/Resources.h"
#include "GameCore/Controller.h"
#include "GameStates/GameOverState.h"
#include "Utils/GameConstants.h"
#include <stdexcept>
#include "factory/GameFactory.h"

bool NameInputState::m_registerit = GameFactory<GameState, float&>::registerit("NameInputState", 
    [](float& a) -> std::unique_ptr<GameState> {
        return std::make_unique<NameInputState>(a);
    });

NameInputState::NameInputState(float score) : m_score(score) {
    m_background.setTexture(Resources::getInstance().getBackgroundTexture("menu"));
    const sf::Texture* tex = m_background.getTexture();
    if (!tex)
        throw std::runtime_error("Failed to load 'menu' background texture for NameInputState");

    m_background.setScale(
        GameConstants::SCREEN_WIDTH / tex->getSize().x,
        GameConstants::SCREEN_HEIGHT / tex->getSize().y
    );
}

void NameInputState::enter(Controller& controller) {
    m_controller = &controller;
    Resources::getInstance().stopBackgroundMusic();
    controller.getWindow().setView(controller.getWindow().getDefaultView());

    if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        m_font = Resources::getInstance().getFont(); 
    }

    m_prompt.setFont(m_font);
    m_prompt.setString(GameConstants::NEW_HIGHSCORE_PROMPT_TEXT);
    m_prompt.setCharacterSize(GameConstants::PROMPT_TEXT_SIZE);
    m_prompt.setFillColor(sf::Color::White);
    m_prompt.setPosition(100.f, GameConstants::PROMPT_Y);

    m_inputText.setFont(m_font);
    m_inputText.setCharacterSize(GameConstants::NAME_TEXT_SIZE);
    m_inputText.setFillColor(sf::Color::Yellow);
    m_inputText.setPosition(100.f, GameConstants::INPUT_TEXT_Y);

    m_inputBox.setSize(GameConstants::NAME_INPUT_BOX_SIZE);
    m_inputBox.setPosition(GameConstants::INPUT_BOX_POS_X, GameConstants::INPUT_BOX_POS_Y);
    m_inputBox.setFillColor(GameConstants::NAME_INPUT_BOX_FILL_COLOR);
    m_inputBox.setOutlineThickness(GameConstants::NAME_INPUT_BOX_OUTLINE_THICKNESS);
    m_inputBox.setOutlineColor(sf::Color::White);
}

std::unique_ptr<GameState> NameInputState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128 && std::isprint(event.text.unicode)) {
            if (m_nameInput.size() < GameConstants::MAX_NAME_LENGTH)
                m_nameInput += static_cast<char>(event.text.unicode);
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace && !m_nameInput.empty()) {
            m_nameInput.pop_back();
        }
        else if (event.key.code == sf::Keyboard::Enter && !m_nameInput.empty()) {
            Resources::getInstance().saveBestScore(m_score, m_nameInput);

            auto next = GameFactory<GameState>::create("GameOverState");

            if (!next)
                throw std::runtime_error("Failed to create GameOverState from NameInputState");
            return next;
        }
    }

    m_inputText.setString(m_nameInput);
    return nullptr;
}

std::unique_ptr<GameState> NameInputState::update(float, Controller&) {
    return nullptr;
}

void NameInputState::render(sf::RenderWindow& window) {
    window.draw(m_background);
    window.draw(m_prompt);
    window.draw(m_inputBox);
    window.draw(m_inputText);
}
