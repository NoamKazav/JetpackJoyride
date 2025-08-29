#include "Objects/GameObject.h"
#include <stdexcept>

void GameObject::render(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

const sf::Sprite& GameObject::getSprite() const {
    return m_sprite;
}

void GameObject::setTexture(const sf::Texture* texture) {
    if (!texture)
        throw std::runtime_error("GameObject::setTexture received null texture");
    m_texture = texture;
    m_sprite.setTexture(*texture);
}

void GameObject::setTextureRect(const sf::IntRect& rect) {
    m_sprite.setTextureRect(rect);
}

void GameObject::setPosition(const sf::Vector2f& pos) {
    m_sprite.setPosition(pos);
}

sf::Vector2f GameObject::getPosition() const {
    return m_sprite.getPosition();
}
