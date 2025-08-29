#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "commands/command.h"

class MenuButton {
public:
    MenuButton(const std::string& textureName, std::unique_ptr<Command> command);

    void setPosition(float x, float y);
    void render(sf::RenderWindow& window) const;
    bool contains(const sf::Vector2f& point) const;
    std::unique_ptr<Command> releaseCommand();
    sf::FloatRect getGlobalBounds() const;
    void setScale(float scaleX, float scaleY);
private:
    sf::Sprite m_sprite;
    std::unique_ptr<Command> m_command;
};
