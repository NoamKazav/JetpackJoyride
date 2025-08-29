#pragma once
#include <SFML/Graphics.hpp>

class Controller;

class GameState {
public:
    virtual ~GameState() = default;

    virtual void enter(Controller& controller) = 0;
    virtual std::unique_ptr<GameState> handleInput(const sf::Event& event) = 0;
    virtual std::unique_ptr<GameState> update(float dt, Controller& controller) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isFinished() const = 0;
};
