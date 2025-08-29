#include "commands/ResumeGameCommand.h"
#include "factory/GameFactory.h"

bool ResumeGameCommand::m_registerit = GameFactory<Command, Controller&, std::shared_ptr<Board>&>::registerit(
    "ResumeGameCommand",
    [](Controller& c, std::shared_ptr<Board>& b)-> std::unique_ptr<Command> {
        return  std::make_unique<ResumeGameCommand>(c, b);
    }
);

void ResumeGameCommand::execute()  {
    auto state = GameFactory<GameState, std::shared_ptr<Board>&>::create("PlayingState", m_board);
    m_controller.setGameState(std::move(state));
}

