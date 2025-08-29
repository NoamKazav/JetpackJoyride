#include "GameStates/GameOverState.h"
#include "GameCore/Controller.h"
#include "GameStates/MenuState.h"
#include "GameCore/Resources.h"
#include <stdexcept>
#include "Utils/GameConstants.h"
#include "factory/GameFactory.h"

bool GameOverState::m_registerit = GameFactory<GameState>::registerit(
    "GameOverState",
    []()-> std::unique_ptr<GameState> {
        return  std::make_unique<GameOverState>();
    }
);

GameOverState::GameOverState() {
    const auto& font = Resources::getInstance().getFont();

    m_title.setFont(font);
    m_title.setString(GameConstants::GAME_OVER_TITLE_TEXT);
    m_title.setCharacterSize(GameConstants::GAME_OVER_TITLE_SIZE);
    m_title.setFillColor(sf::Color::Red);
    m_title.setPosition(GameConstants::GAME_OVER_TITLE_POSITION);

    m_instruction.setFont(font);
    m_instruction.setString(GameConstants::GAME_OVER_INSTRUCTION_TEXT);
    m_instruction.setCharacterSize(GameConstants::GAME_OVER_INSTRUCTION_SIZE);
    m_instruction.setFillColor(sf::Color::White);
    m_instruction.setPosition(GameConstants::GAME_OVER_INSTRUCTION_POSITION);
}

std::unique_ptr<GameState> GameOverState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape)) {

        auto menu = GameFactory<GameState>::create("MenuState");
        if (!menu)
            throw std::runtime_error("Failed to create MenuState from GameOverState");

        return menu;
    }
    return nullptr;
}

std::unique_ptr<GameState> GameOverState::update(float, Controller&) {
    return nullptr;
}

void GameOverState::render(sf::RenderWindow& window) {
    window.draw(m_title);
    window.draw(m_instruction);
}

void GameOverState::enter(Controller& controller) {
    Resources::getInstance().stopBackgroundMusic();
    controller.getWindow().setView(controller.getWindow().getDefaultView());
}

bool GameOverState::isFinished() const {
    return false;
}
