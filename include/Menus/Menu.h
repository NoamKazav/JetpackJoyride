#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Menus/MenuButton.h"
#include "Utils/GameConstants.h"

class Controller;

class Menu {
public:
    void addButton(const std::string& textureName, std::unique_ptr<Command> command);
    void buildDefaultMenu(Controller& controller);

    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);
    std::unique_ptr<Command> pollSelectedCommand();
    void initGraphics(float buttonScale = GameConstants::DEFAULT_BUTTON_SCALE);
    std::vector<std::unique_ptr<MenuButton>>& getButtons() { return m_buttons; }
    void clear();
    void renderButtons(sf::RenderWindow& window) const;
private:
    std::vector<std::unique_ptr<MenuButton>> m_buttons;

    sf::Sprite m_background;
    sf::Sprite m_title;
    int m_selectedIndex = -1;
};
