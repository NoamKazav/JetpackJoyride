#pragma once
#include "commands/MenuCommand.h"

class ShowHighScoresCommand : public MenuCommand {
public:
    using MenuCommand::MenuCommand;
    void execute() override;

private:
    static bool m_registerit;
};
