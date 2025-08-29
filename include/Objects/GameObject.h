#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) const; 
    const sf::Sprite& getSprite() const;
    void setTexture(const sf::Texture* texture);
    void setTextureRect(const sf::IntRect& rect);
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    virtual sf::FloatRect getBounds() const {
        return m_sprite.getGlobalBounds();
    }
    void setRotation(float angle) {
        m_sprite.setRotation(angle);
    }
    void setOrigin(float x, float y) {
        m_sprite.setOrigin(x, y);
    }
    bool isMarkedForDeletion() const { return m_markedForDeletion; }
    void markForDeletion() { m_markedForDeletion = true; }
    void setScale(float x, float y) { m_sprite.setScale(x, y); }
    void setCurrentFrame(const sf::IntRect& rect) {
        m_sprite.setTextureRect(rect);
    }

private:
    sf::Sprite m_sprite;
    const sf::Texture* m_texture = nullptr;
    bool m_markedForDeletion = false;
};
