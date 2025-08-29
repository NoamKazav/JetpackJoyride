#include "GameCore/Controller.h"
#include <iostream>
#include "GameStates/GameState.h"
#include "GameStates/LoadingState.h"
#include <stdexcept>

void Controller::run() {
    m_window.create(
        sf::VideoMode(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT),
        "Jetpack Joyride"
    );

    m_gameState = GameFactory<GameState>::create("LoadingState");
    
    if (!m_gameState)
        throw std::runtime_error("Failed to create initial GameState");

    gameLoop();
}

void Controller::gameLoop() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (m_gameState)
                if (auto next = m_gameState->handleInput(event)) {
                    if (!next)
                        throw std::runtime_error("Null GameState returned from handleInput");
                    next->enter(*this);
                    m_gameState = std::move(next);
                }
        }

        float dt = clock.restart().asSeconds();

        if (m_gameState) {
            if (auto next = m_gameState->update(dt, *this)) {
                if (!next)
                    throw std::runtime_error("Null GameState returned from update");
                next->enter(*this);
                m_gameState = std::move(next);
            }
        }

        m_window.clear();
        if (m_gameState)
            m_gameState->render(m_window);
        m_window.display();
    }
}

void Controller::setGameState(std::unique_ptr<GameState> newState)
{
    m_gameState = std::move(newState);
    if (m_gameState) m_gameState->enter(*this);
}

sf::RenderWindow& Controller::getWindow()
{
    return m_window;
}
