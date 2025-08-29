#include "commands/StartGameCommand.h"
#include "GameCore/Controller.h"
#include "factory/GameFactory.h"

bool StartGameCommand::m_registerit = GameFactory<Command, Controller&>::registerit(
    "Start Game",
    [](Controller& c) -> std::unique_ptr<Command> {
        return std::make_unique<StartGameCommand>(c);
    });


void StartGameCommand::execute() {
    m_controller.setGameState(GameFactory<GameState>::create("IntroState"));
    
}
