#include "Menus/Menu.h"
#include "GameCore/Resources.h"
#include "Utils/GameConstants.h"
#include "GameCore/Controller.h"
#include "factory/GameFactory.h"
#include <stdexcept>

void Menu::addButton(const std::string& textureName, std::unique_ptr<Command> command) {
    auto button = std::move(std::make_unique<MenuButton>(textureName, std::move(command)));

    if (!button)
        throw std::runtime_error("Menu::addButton - Failed to create MenuButton");
    button->setScale(GameConstants::DEFAULT_BUTTON_SCALE, GameConstants::DEFAULT_BUTTON_SCALE);
    m_buttons.emplace_back(std::move(button));
}

void Menu::buildDefaultMenu(Controller& controller) {
    if (auto cmd = GameFactory<Command, Controller&>::create("Start Game", controller))
        addButton("startGame", std::move(cmd));
    else
        throw std::runtime_error("Menu::buildDefaultMenu - Failed to create 'Start Game' command");

    if (auto cmd = GameFactory<Command, Controller&>::create("Instructions", controller))
        addButton("rules", std::move(cmd));
    else
        throw std::runtime_error("Menu::buildDefaultMenu - Failed to create 'Instructions' command");

    if (auto cmd = GameFactory<Command, Controller&>::create("HighScores", controller))
        addButton("record", std::move(cmd));
    else
        throw std::runtime_error("Menu::buildDefaultMenu - Failed to create 'HighScores' command");
}

void Menu::initGraphics(float buttonScale) {
    m_background.setTexture(Resources::getInstance().getBackgroundTexture("menu"));
    if (!m_background.getTexture())
        throw std::runtime_error("Menu::initGraphics - Failed to load background texture");

    m_background.setScale(
        GameConstants::SCREEN_WIDTH / m_background.getTexture()->getSize().x,
        GameConstants::SCREEN_HEIGHT / m_background.getTexture()->getSize().y
    );

    m_title.setTexture(Resources::getInstance().getBackgroundTexture("title"));
    const sf::Texture* titleTex = m_title.getTexture();
    if (!titleTex)
        throw std::runtime_error("Menu::initGraphics - Failed to load title texture");

    float scaleX = GameConstants::MENU_TITLE_SCALE_X;
    float scaleY = GameConstants::MENU_TITLE_SCALE_Y;
    m_title.setScale(scaleX, scaleY);

    sf::FloatRect titleBounds = m_title.getGlobalBounds();
    float centeredX = (GameConstants::SCREEN_WIDTH - titleBounds.width) / 2.f;
    float centeredY = (GameConstants::SCREEN_HEIGHT - titleBounds.height) / 2.f - 
                       GameConstants::MENU_TITLE_Y_OFFSET;
    m_title.setPosition(centeredX, centeredY - GameConstants::MENU_TITLE_EXTRA_Y_SHIFT);

    float centerY = GameConstants::MENU_BUTTONS_CENTER_Y;
    float spacing = GameConstants::MENU_BUTTONS_SPACING;
    float totalHeight = 0.f;
    std::vector<sf::FloatRect> buttonBounds;
    for (const auto& button : m_buttons) {
        buttonBounds.push_back(button->getGlobalBounds());
        totalHeight += button->getGlobalBounds().height;
    }
    totalHeight += spacing * (m_buttons.size() - 1);

    float startY = centerY - totalHeight / 2.f;

    for (size_t i = 0; i < m_buttons.size(); ++i) {
        float x = (GameConstants::SCREEN_WIDTH - buttonBounds[i].width) / 2.f;
        m_buttons[i]->setPosition(x, startY);
        startY += buttonBounds[i].height + spacing;
    }
}

void Menu::clear() {
    m_buttons.clear();
    m_selectedIndex = -1;
}

void Menu::render(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    window.draw(m_background);
    window.draw(m_title);
    for (const auto& btn : m_buttons)
        btn->render(window);
}

void Menu::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

        for (size_t i = 0; i < m_buttons.size(); ++i) {
            if (m_buttons[i]->contains(mousePos)) {
                m_selectedIndex = static_cast<int>(i);
                break;
            }
        }
    }
}

std::unique_ptr<Command> Menu::pollSelectedCommand() {
    if (m_selectedIndex != -1 && m_selectedIndex < static_cast<int>(m_buttons.size())) {
        auto cmd = m_buttons[m_selectedIndex]->releaseCommand();
        m_selectedIndex = -1;
        return cmd;
    }
    return nullptr;
}

void Menu::renderButtons(sf::RenderWindow& window) const {
    for (const auto& btn : m_buttons)
        btn->render(window);
}
