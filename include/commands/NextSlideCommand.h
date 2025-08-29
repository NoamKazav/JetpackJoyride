#pragma once
#include "MenuCommand.h"

class InstructionsState;

class NextSlideCommand : public MenuCommand {
public:
    NextSlideCommand(InstructionsState& state);
    void execute() override;

private:
    InstructionsState& m_state;
    static bool m_registerit;
};
