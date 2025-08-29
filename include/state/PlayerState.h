#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Player;

class PlayerState {
public:
    virtual ~PlayerState() = default;

    virtual std::unique_ptr<PlayerState> handleInput(const sf::Event&) = 0;
    virtual std::unique_ptr<PlayerState> update(Player& player, float dt) = 0;
    virtual void enter(Player& player) {};
    virtual void renderExtras(const Player& player, sf::RenderWindow& window) {};
protected:
    void drawShieldIfNeeded(const Player& player, sf::RenderWindow& window) const;
};