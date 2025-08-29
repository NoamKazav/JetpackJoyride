#include "Menus/MenuButton.h"
#include "GameCore/Resources.h"
#include <stdexcept>

MenuButton::MenuButton(const std::string& textureName, std::unique_ptr<Command> command)
    : m_command(std::move(command)) {
    m_sprite.setTexture(Resources::getInstance().getButtonTexture(textureName));
    if (!m_sprite.getTexture())
        throw std::runtime_error("MenuButton: failed to load texture: " + textureName);
}

void MenuButton::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

void MenuButton::render(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

bool MenuButton::contains(const sf::Vector2f& point) const {
    return m_sprite.getGlobalBounds().contains(point);
}

std::unique_ptr<Command> MenuButton::releaseCommand() {

    return std::move(m_command);
}

sf::FloatRect MenuButton::getGlobalBounds() const {
    return m_sprite.getGlobalBounds();
}

void MenuButton::setScale(float scaleX, float scaleY) {
    m_sprite.setScale(scaleX, scaleY);
}
