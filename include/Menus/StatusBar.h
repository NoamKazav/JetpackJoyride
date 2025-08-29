#pragma once
#include <SFML/Graphics.hpp>
#include "Utils/GameConstants.h"

class StatusBar {
public:
    StatusBar();

    void update(float distance, int coins, float best);
    void render(sf::RenderWindow& window);

private:
    sf::Font m_font;
    sf::Text m_distanceText;
    sf::Text m_distanceLabel;

    sf::Text m_bestText;
    sf::Text m_coinText;
    sf::Text m_coinLabel;

    sf::RectangleShape m_background;
    sf::Sprite m_coinIcon;  

    void setupText(sf::Text& text, const sf::Vector2f& position, 
                   unsigned int size = GameConstants::STATUSBAR_TEXT_SIZE);

};
