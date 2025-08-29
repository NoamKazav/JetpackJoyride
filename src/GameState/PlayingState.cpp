#include "GameStates/PlayingState.h"
#include "commands/OpenPauseMenuCommand.h"
#include "GameCore/Controller.h"
#include "Utils/GameConstants.h"
#include "GameStates/NameInputState.h"
#include "GameStates/GameOverState.h"
#include <stdexcept>
#include "factory/GameFactory.h"

bool m_registerit = GameFactory<GameState, std::shared_ptr<Board>&>::registerit("PlayingState",
    [](std::shared_ptr<Board>& b) -> std::unique_ptr<GameState> {
        return std::make_unique<PlayingState>(b);
    });

PlayingState::PlayingState(sf::RenderWindow& window) {
    m_board = std::make_shared<Board>(window);
    if (!m_board)
        throw std::runtime_error("PlayingState: failed to create Board");
}

PlayingState::PlayingState(std::shared_ptr<Board> existingBoard)
    : m_board(std::move(existingBoard)) {
    if (!m_board)
        throw std::runtime_error("PlayingState: received null Board");
}

void PlayingState::enter(Controller& controller) {
    Resources::getInstance().playBackgroundMusic();

    auto pauseCmd = GameFactory<Command, Controller&, std::shared_ptr<Board>&>::create("pause", controller, m_board);
    if (!pauseCmd)
        throw std::runtime_error("PlayingState: failed to create pause command");

    m_board->addCommandButton("pause", {GameConstants::SCREEN_WIDTH - 
                                        GameConstants::PAUSE_BUTTON_OFFSET_X,
                                        GameConstants::PAUSE_BUTTON_POS_Y }, 
                                        std::move(pauseCmd));

    auto pauseCmd2 = GameFactory<Command, Controller&, std::shared_ptr<Board>&>::create("pause", controller, m_board);
    if (!pauseCmd2)
        throw std::runtime_error("PlayingState: failed to create second pause command");

    m_board->addCommandButton("pause", {GameConstants::SCREEN_WIDTH - 
                                        GameConstants::PAUSE_BUTTON_OFFSET_X,
                                        GameConstants::PAUSE_BUTTON_POS_Y }, 
                                        std::move(pauseCmd2));
}

void PlayingState::render(sf::RenderWindow& window) {
    if (!m_board)
        throw std::runtime_error("PlayingState: Board is null in render");
    m_board->render();
}

std::unique_ptr<GameState> PlayingState::handleInput(const sf::Event& event) {
    if (!m_board)
        throw std::runtime_error("PlayingState: Board is null in handleInput");
    m_board->handleEvent(event);
    return nullptr;
}

std::unique_ptr<GameState> PlayingState::update(float dt, Controller& controller) {
    if (!m_board)
        throw std::runtime_error("PlayingState: Board is null in update");

    m_board->update(dt);

    if (m_board->isGameOver()) {
        float finalDistance = m_board->getDistance();

        if (finalDistance > Resources::getInstance().getBestScore()) {
            auto next = GameFactory<GameState, float&>::create("NameInputState", finalDistance);
            if (!next)
                throw std::runtime_error("PlayingState: failed to create NameInputState");
            return next;
        }

        auto gameOver = GameFactory<GameState>::create("GameOverState");
        if (!gameOver)
            throw std::runtime_error("PlayingState: failed to create GameOverState");
        return gameOver;
    }

    return nullptr;
}
