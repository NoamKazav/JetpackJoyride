#include "state/PlayerState.h"
#include "Objects/Player.h"
#include "GameCore/Resources.h"
#include "Utils/GameConstants.h"

void PlayerState::drawShieldIfNeeded(const Player& player, sf::RenderWindow& window) const {
    if (!player.isInvincible())
        return;

    auto& tex = Resources::getInstance().getObjectTexture(ObjectType::Bubble);
    sf::Sprite bubbleSprite;
    bubbleSprite.setTexture(tex);

    auto bounds = player.getSprite().getGlobalBounds();
    auto texSize = tex.getSize();

    float radius = std::max(bounds.width, bounds.height) / 2.f + GameConstants::SHIELD_MARGIN;
    float diameter = 2.f * radius;

    float scale = diameter / static_cast<float>(texSize.x);
    bubbleSprite.setScale(scale, scale);
    bubbleSprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
    bubbleSprite.setPosition(bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f);
    bubbleSprite.setColor(GameConstants::SHIELD_TEXTURE_COLOR);

    window.draw(bubbleSprite);

    sf::CircleShape circle;
    float circleRadius = radius - GameConstants::SHIELD_RADIUS_OFFSET;
    circle.setRadius(circleRadius);
    circle.setOrigin(circleRadius, circleRadius);
    circle.setPosition(bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f);

    circle.setFillColor(GameConstants::SHIELD_FILL_COLOR);
    circle.setOutlineColor(GameConstants::SHIELD_OUTLINE_COLOR);
    circle.setOutlineThickness(GameConstants::SHIELD_OUTLINE_THICKNESS);

    window.draw(circle);
}
