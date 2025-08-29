#pragma once
#include "GameStates/GameState.h"
#include <SFML/Graphics.hpp>
#include "Utils/GameConstants.h"



class IntroState : public GameState {
public:
    IntroState();
    void enter(Controller& controller);
    std::unique_ptr<GameState> handleInput(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float dt, Controller& controller) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override { return false; }

private:
    sf::Sprite m_sprite;
    const std::vector<sf::IntRect>* m_frames = nullptr;
    float m_elapsed = 0.f;
    float m_timeSinceLastFrame = 0.f;
    const float m_frameTime = GameConstants::INTRO_FRAME_TIME;
    std::size_t m_currentFrame = 0;
    static bool m_registerit;
};
