#pragma once
#include <SFML/Graphics.hpp>
#include "Menus/Menu.h"
#include "commands/command.h"
#include "GameStates/GameState.h"
#include "GameCore/Board.h"
#include "GameStates/IntroState.h"

class Controller {
public:
    void run();       
    void gameLoop(); 
    void setGameState(std::unique_ptr<GameState> newState);
    sf::RenderWindow& getWindow();
private:
    sf::RenderWindow m_window;
    Menu m_menu;
    std::unique_ptr<GameState> m_gameState;
};
