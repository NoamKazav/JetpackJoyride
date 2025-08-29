#pragma once
#include "commands/Command.h"
#include "GameCore/Controller.h"
#include "GameStates/MenuState.h"

class ExitToMenuCommand : public Command {
public:
    ExitToMenuCommand(Controller& controller) : m_controller(controller) {}

    void execute() override;

private:
    static bool m_registerit;
    Controller& m_controller;
};
