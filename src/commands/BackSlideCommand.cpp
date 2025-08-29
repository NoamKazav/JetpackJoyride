#include "commands/BackSlideCommand.h"
#include "GameStates/InstructionsState.h"
#include "GameStates/GameState.h"
#include "GameStates/MenuState.h"
#include "factory/GameFactory.h"
#include "GameCore/Controller.h"
#include <stdexcept>

bool BackSlideCommand::m_registerit = GameFactory<Command, InstructionsState&>::registerit(
    "BackSlide",
    [](InstructionsState& s)-> std::unique_ptr<Command> {
        return  std::make_unique<BackSlideCommand>(s);
    }
);

BackSlideCommand::BackSlideCommand(InstructionsState& state)
    : MenuCommand(*state.getController()), m_state(state) {}

void BackSlideCommand::execute() {
    if (m_state.getCurrentSlideIndex() == 0) {
        auto state = GameFactory<GameState>::create("MenuState");
        if (!state)
            throw std::runtime_error("Failed to create MenuState");
        m_controller.setGameState(std::move(state));
    }
    else {
        int current = m_state.getCurrentSlideIndex();
        if (current <= 0)
            throw std::logic_error("Slide index is already zero");
        m_state.setCurrentSlideIndex(current - 1);
        m_state.updateSlideAndButtons();
    }
}
