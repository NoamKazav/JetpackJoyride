#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Utils/GameConstants.h"
#include "Resources.h"
#include "Utils/ObjectType.h"
#include "Objects/Player.h"
#include "factory/GameFactory.h"
#include "Objects/GameObject.h"
#include "Objects/StaticObject.h"
#include "Spawners/ObjectSpawner.h"
#include "Spawners/CoinSpawner.h"
#include "Spawners/SpawnerManager.h"
#include "Spawners/ScientistSpawner.h"
#include "Menus/StatusBar.h"
#include "commands/command.h"
#include "Menus/MenuButton.h"

class Player;

class Board {
public:
    Board(sf::RenderWindow& window);
    void update(float dt);
    void render();
    void handleEvent(const sf::Event& event);
    bool isGameOver() const;
    float getScrollSpeed() const;
    void setScrollSpeed(float speed);
    float getDistance() const;
    void addCommandButton(const std::string& textureName, sf::Vector2f position, std::unique_ptr<Command> cmd);
private:
    void scrollView(float dt);
    void drawBackground();
    void removeOffscreenObjects();
    void removeCollectedObjects();
    float getViewLeft() const;
    float getViewRight() const;

    sf::RenderWindow& m_window;
    sf::View m_view;

    const sf::Texture* m_backgroundTexture = nullptr;
    sf::Sprite m_backgroundSprite;

    const sf::Texture* m_introBackgroundTexture = nullptr;
    sf::Sprite m_introBackgroundSprite;

    std::unique_ptr<Player> m_player;
    std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
    std::vector<std::unique_ptr<MovingObject>> m_movingObjects;
    SpawnerManager m_spawnerManager;
    bool m_effectAdded = false; 
    float m_scrollSpeed = GameConstants::SCROLL_SPEED;
    StatusBar m_statusBar;
    sf::Sprite m_stopButton;
    std::vector<MenuButton> m_commandButtons;
};
