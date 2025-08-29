#pragma once
#include "Command.h"

class Board
class BoardCommand : public Command {
public:
    BoardCommand(Board& board) : m_board(board) {}
protected:
    Board& m_board;
};
