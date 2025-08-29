#include "commands/ShowHighScoresCommand.h"
#include "GameStates/HighScoresState.h"
#include "GameCore/Controller.h"
#include "factory/GameFactory.h"

bool ShowHighScoresCommand::m_registerit = GameFactory<Command, Controller&>::registerit(
    "HighScores",
    [](Controller& c)  -> std::unique_ptr<Command> {
        return std::make_unique<ShowHighScoresCommand>(c);
    }
);

void ShowHighScoresCommand::execute() {
    m_controller.setGameState (GameFactory<GameState>::create("HighScoresState"));
}
