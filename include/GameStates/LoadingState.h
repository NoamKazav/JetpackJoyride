#pragma once
#include "GameStates/GameState.h"
#include <SFML/Graphics.hpp>
#include "Utils/GameConstants.h"

class LoadingState : public GameState {
public:
    LoadingState();
    void enter(Controller& controller) override {};
    std::unique_ptr<GameState> handleInput(const sf::Event& event) override { return nullptr; };
    std::unique_ptr<GameState> update(float dt, Controller& controller) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override { return false; }

private:
    sf::Sprite m_sprite;
    sf::Font m_font;
    sf::Text m_loadingText;
    float m_elapsed = 0.f;
    const float m_loadingDuration = GameConstants::LOADING_DURATION;
    static bool m_registerit;
};
