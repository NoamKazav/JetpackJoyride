#pragma once

#include "GameStates/GameState.h"
#include "Menus/Menu.h"
#include <memory>

class Controller;
class GameState;

class PauseMenuState : public GameState {
public:
    PauseMenuState(sf::RenderWindow& window, std::unique_ptr<GameState> previous);

    void enter(Controller& controller) override;
    std::unique_ptr<GameState> handleInput(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float dt, Controller& controller) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override { return false; }

private:
    Menu m_menu;
    std::unique_ptr<GameState> m_previousState;
    Controller* m_controller = nullptr;
    static bool m_registerit;
};