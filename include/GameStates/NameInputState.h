#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <string>

class Controller;

class NameInputState : public GameState {
public:
    NameInputState(float score);
    void enter(Controller& controller) override;
    std::unique_ptr<GameState> handleInput(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float dt, Controller& controller) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override { return false; }
private:
    sf::Font m_font;
    Controller* m_controller = nullptr;
    float m_score;
    std::string m_nameInput;
    sf::Text m_prompt;
    sf::Text m_inputText;
    sf::RectangleShape m_inputBox;
    sf::Sprite m_background;
    static bool m_registerit;
};
