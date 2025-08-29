#pragma once
#include "GameStates/GameState.h"
#include <SFML/Graphics.hpp>

class GameOverState : public GameState {
public:
    GameOverState();
    std::unique_ptr<GameState> handleInput(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float, Controller&) override;
    void render(sf::RenderWindow& window) override;
    void enter(Controller& controller) override;
    bool isFinished() const override;

private:
    sf::Text m_title;
    sf::Text m_instruction;
    static bool m_registerit;
};
