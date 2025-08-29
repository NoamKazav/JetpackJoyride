#include "commands/RestartGameCommand.h"
#include "factory/GameFactory.h"

bool RestartGameCommand::m_registerit = GameFactory<Command, Controller&>::registerit(
    "RestartGameCommand",
    [](Controller& c)-> std::unique_ptr<Command> {
        return  std::make_unique<RestartGameCommand>(c);
    }
);

void RestartGameCommand::execute()  {
    m_controller.setGameState(GameFactory<GameState>::create("IntroState"));

}