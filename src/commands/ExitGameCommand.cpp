#include "commands/ExitGameCommand.h"
#include "factory/GameFactory.h"

bool ExitGameCommand::m_registerit = GameFactory<Command>::registerit(
    "Exit",
    []() ->std::unique_ptr<Command> {
        return std::make_unique<ExitGameCommand>();
    });