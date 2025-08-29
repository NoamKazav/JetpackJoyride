#pragma once
#include "MenuCommand.h"
#include "GameStates/MenuState.h"

class StartGameCommand : public MenuCommand {
public:
    using MenuCommand::MenuCommand; 
    void execute() override;
private:
    static bool m_registerit;
};