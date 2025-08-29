#include "commands/NextSlideCommand.h"
#include "GameStates/InstructionsState.h"
#include "factory/GameFactory.h"
#include "GameCore/Controller.h"
#include <stdexcept>

bool NextSlideCommand::m_registerit = GameFactory<Command, InstructionsState&>::registerit(
    "NextSlide",
    [](InstructionsState& s)-> std::unique_ptr<Command> {
        return  std::make_unique<NextSlideCommand>(s);
    }
);

NextSlideCommand::NextSlideCommand(InstructionsState& state)
    : MenuCommand(*state.getController()), m_state(state) {}

void NextSlideCommand::execute() {
    int current = m_state.getCurrentSlideIndex();
    int count = m_state.getSlideCount();

    if (current + 1 < count) {
        m_state.setCurrentSlideIndex(current + 1);
        m_state.updateSlideAndButtons();
    }
}
