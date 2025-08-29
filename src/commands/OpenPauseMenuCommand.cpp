#include "commands/OpenPauseMenuCommand.h"
#include "GameStates/PauseMenuState.h"
#include "GameStates/PlayingState.h"
#include "GameCore/Board.h"

bool OpenPauseMenuCommand::m_registerit = GameFactory<Command, Controller&, std::shared_ptr<Board>&>::registerit(
    "pause",
    [](Controller& c, std::shared_ptr<Board>& b)-> std::unique_ptr<Command> {
        return  std::make_unique<OpenPauseMenuCommand>(c, b);
    }
);

OpenPauseMenuCommand::OpenPauseMenuCommand(Controller& controller, std::shared_ptr<Board> board)
    : m_controller(controller), m_board(std::move(board)) {}

void OpenPauseMenuCommand::execute() {
    auto playing = GameFactory<GameState, std::shared_ptr<Board>&>::create("PlayingState", m_board);
    auto pause = std::make_unique<PauseMenuState>(m_controller.getWindow(), std::move(playing));
    m_controller.setGameState(std::move(pause));
}
