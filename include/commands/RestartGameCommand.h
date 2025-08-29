#pragma once
#include "commands/Command.h"
#include "GameCore/Controller.h"
#include "GameStates/IntroState.h"

class RestartGameCommand : public Command {
public:
    RestartGameCommand(Controller& controller) : m_controller(controller) {}

    void execute();

private:
    Controller& m_controller;
    static bool m_registerit;
};
