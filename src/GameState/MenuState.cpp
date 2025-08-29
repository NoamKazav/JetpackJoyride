#include "GameStates/MenuState.h"
#include "GameCore/Controller.h"
#include <stdexcept>

bool MenuState::m_registerit = GameFactory<GameState>::registerit("MenuState", []() -> std::unique_ptr<GameState> {
    return std::make_unique<MenuState>();
    });

MenuState::MenuState() {}

void MenuState::enter(Controller& controller) {
    m_menu.buildDefaultMenu(controller);
    if (m_menu.getButtons().empty())
        throw std::runtime_error("MenuState: Failed to build menu buttons");

    m_menu.initGraphics(1.0f);
}

std::unique_ptr<GameState> MenuState::handleInput(const sf::Event& event) {
    m_menu.handleEvent(event);
    return nullptr;
}

std::unique_ptr<GameState> MenuState::update(float, Controller&) {
    if (auto cmd = m_menu.pollSelectedCommand()) {
        if (!cmd)
            throw std::runtime_error("MenuState: Command is null after selection");
        cmd->execute();
    }
    return nullptr;
}

void MenuState::render(sf::RenderWindow& window) {
    m_menu.render(window);
}
