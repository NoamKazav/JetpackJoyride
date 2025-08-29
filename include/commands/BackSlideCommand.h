#pragma once
#include "MenuCommand.h"

class InstructionsState;

class BackSlideCommand : public MenuCommand {
public:
    BackSlideCommand(InstructionsState& state);
    void execute() override;

private:
    InstructionsState& m_state;
    static bool m_registerit;
};
