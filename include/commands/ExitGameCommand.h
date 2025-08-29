#include "commands/command.h"
class ExitGameCommand : public Command {
public:
    virtual void execute() override {
        std::cout << "Exiting the game...\n";
        exit(0);
    }
private:
    static bool m_registerit;
};