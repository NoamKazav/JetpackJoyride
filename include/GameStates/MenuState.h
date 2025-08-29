#pragma once

#include "GameStates/GameState.h"
#include "Menus/Menu.h"
#include <SFML/Graphics.hpp>

class MenuState : public GameState {
public:
    MenuState();

    std::unique_ptr<GameState> handleInput(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float dt, Controller& controller) override;
    void render(sf::RenderWindow& window) override;
    void enter(Controller& controller) override;
    bool isFinished() const override { return false; }

private:
    Menu m_menu;
   static bool m_registerit;
};
