#pragma once
#include "Command.h"
class Controller;

class MenuCommand : public Command {
public:
    MenuCommand(Controller& controller) : m_controller(controller) {}

protected:
    Controller& m_controller;  
};