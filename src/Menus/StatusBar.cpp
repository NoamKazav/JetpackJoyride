#include "Menus/StatusBar.h"
#include "GameCore/Resources.h"
#include "Utils/GameConstants.h"
#include "Utils/ObjectType.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>

StatusBar::StatusBar() {
    if (!m_font.loadFromFile(GameConstants::FONT_PATH)) {
        m_font = Resources::getInstance().getFont(); 
    }

    m_background.setSize(GameConstants::STATUSBAR_SIZE);
    m_background.setPosition(GameConstants::STATUSBAR_POSITION);
    m_background.setFillColor(GameConstants::NAME_INPUT_BOX_FILL_COLOR);
    m_background.setOutlineColor(sf::Color::White);
    m_background.setOutlineThickness(2.f);

    setupText(m_distanceLabel, GameConstants::STATUSBAR_DISTANCE_LABEL_POS);
    m_distanceLabel.setString("DISTANCE:");

    setupText(m_distanceText, GameConstants::STATUSBAR_DISTANCE_TEXT_POS);

    setupText(m_bestText, GameConstants::STATUSBAR_BEST_TEXT_POS);
    m_bestText.setString("BEST:");

    setupText(m_coinLabel, GameConstants::STATUSBAR_COIN_LABEL_POS);
    m_coinLabel.setString("COINS:");

    setupText(m_coinText, GameConstants::STATUSBAR_COIN_TEXT_POS);
    m_coinText.setString("0000");

    m_coinIcon.setTexture(Resources::getInstance().getObjectTexture(ObjectType::Coin));
    if (!m_coinIcon.getTexture())
        throw std::runtime_error("StatusBar: failed to load coin texture");

    m_coinIcon.setScale(GameConstants::DEFAULT_BUTTON_SCALE, GameConstants::DEFAULT_BUTTON_SCALE);
    m_coinIcon.setPosition(GameConstants::STATUSBAR_COIN_ICON_POSITION);

    const auto* frames = Resources::getInstance().getAnimationFrames("coin");
    if (!frames || frames->empty())
        throw std::runtime_error("StatusBar: missing animation frames for coin");

    m_coinIcon.setTextureRect((*frames)[0]);
}

void StatusBar::setupText(sf::Text& text, const sf::Vector2f& pos, unsigned int size) {
    text.setFont(m_font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setPosition(pos);
}

void StatusBar::update(float distance, int coins, float best) {
    m_distanceText.setString(std::to_string(static_cast<int>(distance)) + "M");
    m_bestText.setString("BEST: " + std::to_string(static_cast<int>(best)) + "M");

    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << coins;
    m_coinText.setString(oss.str());
}

void StatusBar::render(sf::RenderWindow& window) {
    window.draw(m_background);
    window.draw(m_distanceLabel);
    window.draw(m_distanceText);
    window.draw(m_bestText);
    window.draw(m_coinLabel);
    window.draw(m_coinText);
    window.draw(m_coinIcon);
}
