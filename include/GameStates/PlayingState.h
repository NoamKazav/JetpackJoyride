#pragma once
#include "GameStates/GameState.h"
#include <memory>
#include "GameCore/Board.h"
#include "GameStates/GameOverState.h"

class Controller;

class PlayingState : public GameState {
public:
    PlayingState(sf::RenderWindow& window);
    PlayingState(std::shared_ptr<Board> existingBoard);

    void enter(Controller& controller) override;
    std::unique_ptr<GameState> handleInput(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float dt, Controller& controller) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override { return false; }
    std::shared_ptr<Board> getBoard() const { return m_board; }

private:
    std::shared_ptr<Board> m_board;
    static bool m_registerit;
};
