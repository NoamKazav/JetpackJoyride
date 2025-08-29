#pragma once
#include "commands/Command.h"
#include "GameCore/Controller.h"
#include "GameStates/GameState.h"
#include <memory>
#include "GameStates/PlayingState.h"
class ResumeGameCommand : public Command {
public:
    ResumeGameCommand(Controller& controller, std::shared_ptr<Board> board)
        : m_controller(controller), m_board(std::move(board)) {}

    void execute();

private:
    Controller& m_controller;
    std::shared_ptr<Board> m_board;
    static bool m_registerit;
};

