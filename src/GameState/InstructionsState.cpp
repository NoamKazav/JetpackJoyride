#include "GameStates/InstructionsState.h"
#include "GameStates/MenuState.h"
#include "GameCore/Resources.h"
#include "Utils/GameConstants.h"
#include "commands/BackSlideCommand.h"
#include "commands/NextSlideCommand.h"
#include "factory/GameFactory.h"
#include <stdexcept>

bool InstructionsState::m_registerit = GameFactory<GameState>::registerit("InstructionsState",
    []() -> std::unique_ptr<GameState> {
        return std::make_unique<InstructionsState>();
    });

InstructionsState::InstructionsState() {}

void InstructionsState::enter(Controller& controller) {
    m_controller = &controller;
    updateSlideAndButtons();
}

void InstructionsState::loadSlide() {
    const std::string& texName = m_slideNames[m_currentSlideIndex];
    m_slideSprite.setTexture(Resources::getInstance().getBackgroundTexture(texName));

    if (!m_slideSprite.getTexture())
        throw std::runtime_error("Failed to load slide texture: " + texName);

    m_slideSprite.setPosition(0, 0);

    float scaleX = GameConstants::SCREEN_WIDTH / m_slideSprite.getTexture()->getSize().x;
    float scaleY = GameConstants::SCREEN_HEIGHT / m_slideSprite.getTexture()->getSize().y;
    m_slideSprite.setScale(scaleX, scaleY);
}

void InstructionsState::updateSlideAndButtons() {
    loadSlide();

    m_menu.clear();

    m_menu.addButton("back1",  GameFactory<Command, InstructionsState&>::create("BackSlide", *this));
    m_menu.addButton("back", GameFactory<Command, InstructionsState&>::create("NextSlide", *this));
    float scale = 0.5f;
    float y = GameConstants::SCREEN_HEIGHT - 100.f;

    auto& backButton = m_menu.getButtons()[0];
    auto& nextButton = m_menu.getButtons()[1];

    if (!backButton || !nextButton)
        throw std::runtime_error("Failed to create navigation buttons in InstructionsState");

    backButton->setScale(scale, scale);
    nextButton->setScale(scale, scale);

    sf::FloatRect nextBounds = nextButton->getGlobalBounds();

    backButton->setPosition(GameConstants::INSTRUCTIONS_BUTTON_SIDE_MARGIN, y);
    nextButton->setPosition(GameConstants::SCREEN_WIDTH - 
                            nextBounds.width - GameConstants::INSTRUCTIONS_BUTTON_SIDE_MARGIN, y);
}

std::unique_ptr<GameState> InstructionsState::handleInput(const sf::Event& event) {
    m_menu.handleEvent(event);
    return nullptr;
}

std::unique_ptr<GameState> InstructionsState::update(float, Controller&) {
    if (auto cmd = m_menu.pollSelectedCommand())
        cmd->execute();
    return nullptr;
}

void InstructionsState::render(sf::RenderWindow& window) {
    window.draw(m_slideSprite);
    m_menu.renderButtons(window);
}
