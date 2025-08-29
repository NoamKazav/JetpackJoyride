#pragma once
#include "GameStates/GameState.h"
#include <SFML/Graphics.hpp>
#include <vector>

class HighScoresState : public GameState {
public:
    void enter(Controller& controller) override;
    std::unique_ptr<GameState> handleInput(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float dt, Controller& controller) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override { return false; }
private:
    sf::Font m_font;
    Controller* m_controller = nullptr;
    std::vector<sf::Text> m_scoreTexts;
    sf::Sprite m_backButton;
    sf::FloatRect m_backButtonBounds;
    sf::Sprite m_background;
    static bool m_registerit;
};
