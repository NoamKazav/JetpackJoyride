#include "commands/ExitToMenuCommand.h"

bool ExitToMenuCommand::m_registerit = GameFactory<Command, Controller&>::registerit(
    "ExitToMenuCommand",
    [](Controller& c)-> std::unique_ptr<Command> {
        return  std::make_unique<ExitToMenuCommand>(c);
    }
);

void ExitToMenuCommand::execute()  
{
    m_controller.setGameState(GameFactory<GameState>::create("MenuState"));
}

