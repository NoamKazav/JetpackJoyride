#include "GameStates/PauseMenuState.h"
#include "GameCore/Controller.h"
#include "commands/ResumeGameCommand.h"
#include "commands/RestartGameCommand.h"
#include "commands/ExitToMenuCommand.h"
#include "GameStates/PlayingState.h"
#include "Utils/GameConstants.h"
#include <stdexcept>
#include "factory/GameFactory.h"

bool PauseMenuState::m_registerit = GameFactory<GameState, sf::RenderWindow &, std::unique_ptr<GameState>&>::registerit(
    "PauseMenuState",
    [](sf::RenderWindow& w , std::unique_ptr<GameState>& p)-> std::unique_ptr<GameState> {
        return  std::make_unique<PauseMenuState>(w, std::move(p));
    }
);

PauseMenuState::PauseMenuState(sf::RenderWindow& window, std::unique_ptr<GameState> previous)
    : m_previousState(std::move(previous)) {}

void PauseMenuState::enter(Controller& controller) {
    Resources::getInstance().stopBackgroundMusic();
    m_controller = &controller;

    auto* playingPtr = dynamic_cast<PlayingState*>(m_previousState.get());
    if (!playingPtr)
        throw std::runtime_error("PauseMenuState: previous state is not PlayingState");

    std::shared_ptr<Board> board = playingPtr->getBoard();
    if (!board)
        throw std::runtime_error("PauseMenuState: failed to get Board from PlayingState");


    m_menu.addButton("continue", GameFactory<Command, Controller&, std::shared_ptr<Board>&>::create("ResumeGameCommand", controller, board));
    m_menu.addButton("restart", GameFactory<Command, Controller&>::create("RestartGameCommand", controller));
    m_menu.addButton("backToMenu", GameFactory<Command, Controller&>::create("ExitToMenuCommand", controller));


    if (m_menu.getButtons().empty())
        throw std::runtime_error("PauseMenuState: failed to initialize menu buttons");

    m_menu.initGraphics(GameConstants::DEFAULT_BUTTON_SCALE);
}

std::unique_ptr<GameState> PauseMenuState::handleInput(const sf::Event& event) {
    m_menu.handleEvent(event);
    return nullptr;
}

std::unique_ptr<GameState> PauseMenuState::update(float, Controller&) {
    if (auto cmd = m_menu.pollSelectedCommand()) {
        if (!cmd)
            throw std::runtime_error("PauseMenuState: selected command is null");
        cmd->execute();
    }
    return nullptr;
}

void PauseMenuState::render(sf::RenderWindow& window) {
    if (m_previousState)
        m_previousState->render(window);
    m_menu.render(window);
}
