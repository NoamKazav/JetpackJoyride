#include "commands/ShowInstructionsCommand.h"
#include "GameStates/InstructionsState.h"
#include "GameCore/Controller.h"
#include "factory/GameFactory.h"

bool ShowInstructionsCommand::m_registerit =
GameFactory<Command, Controller& >::registerit(
    "Instructions",
    [](Controller& c) -> std::unique_ptr<Command> {
        return std::make_unique<ShowInstructionsCommand>(c);
    }
);

void ShowInstructionsCommand::execute() {
    m_controller.setGameState(GameFactory<GameState>::create("InstructionsState"));
}
