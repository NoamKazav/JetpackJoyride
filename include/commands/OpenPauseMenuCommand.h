#pragma once
#include "commands/Command.h"
#include "GameCore/Controller.h"
#include <memory>

class Board;

class OpenPauseMenuCommand : public Command {
public:
    OpenPauseMenuCommand(Controller& controller, std::shared_ptr<Board> board);

    void execute() override;

private:
    Controller& m_controller;
    static bool m_registerit;
    std::shared_ptr<Board> m_board;
};
