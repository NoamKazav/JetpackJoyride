#include "GameCore/Board.h"
#include <cmath>
#include "CollisionHandler.h"
#include <iostream>
#include "Utils/GameConstants.h"
#include <stdexcept>

Board::Board(sf::RenderWindow& window)
    : m_window(window), m_view(sf::FloatRect(0, 0, GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT)) {

    m_introBackgroundTexture = &Resources::getInstance().getBackgroundTexture("intro");
    if (!m_introBackgroundTexture)
        throw std::runtime_error("Intro background texture missing");
    m_introBackgroundSprite.setTexture(*m_introBackgroundTexture);

    m_backgroundTexture = &Resources::getInstance().getBackgroundTexture("game");
    if (!m_backgroundTexture)
        throw std::runtime_error("Game background texture missing");
    m_backgroundSprite.setTexture(*m_backgroundTexture);

    m_window.setView(m_view);

    m_player = std::unique_ptr<Player>(
        static_cast<Player*>(GameFactory<GameObject>::create("Player").release())
    );
    if (!m_player)
        throw std::runtime_error("Failed to create Player");

    if (auto spawner = GameFactory<StaticObjectSpawner>::create("LightSpawner"))
        m_spawnerManager.addStaticSpawner(std::move(spawner));
    else
        throw std::runtime_error("Failed to create LightSpawner");

    if (auto spawner = GameFactory<StaticObjectSpawner>::create("CoinSpawner"))
        m_spawnerManager.addStaticSpawner(std::move(spawner));
    else
        throw std::runtime_error("Failed to create CoinSpawner");

    if (auto spawner = GameFactory<StaticObjectSpawner>::create("LaserSpawner"))
        m_spawnerManager.addStaticSpawner(std::move(spawner));
    else
        throw std::runtime_error("Failed to create LaserSpawner");

    if (auto spawner = GameFactory<StaticObjectSpawner>::create("GiftSpawner"))
        m_spawnerManager.addStaticSpawner(std::move(spawner));
    else
        throw std::runtime_error("Failed to create GiftSpawner");

    if (auto spawner = GameFactory<MovingObjectSpawner>::create("ScientistSpawner"))
        m_spawnerManager.addMovingSpawner(std::move(spawner));
    else
        throw std::runtime_error("Failed to create ScientistSpawner");

    if (auto spawner = GameFactory<MovingObjectSpawner, Player&>::create("MissileSpawner", *m_player)) {
        m_spawnerManager.addMovingSpawner(std::move(spawner));
    }
    else {
        throw std::runtime_error("Failed to create MissileSpawner");
    }

    float viewLeft = getViewLeft();
    m_player->anchorToViewLeft(viewLeft);
}

void Board::update(float dt) {
    scrollView(dt);

    if (m_player->isDead()) {
        m_scrollSpeed *= GameConstants::DEATH_SCROLL_DAMPING;
        if (m_scrollSpeed < GameConstants::MIN_SCROLL_SPEED)
            m_scrollSpeed = 0.f;
    }
    else {
        const float maxSpeed = GameConstants::MAX_SCROLL_SPEED;
        const float acceleration = GameConstants::SCROLL_ACCELERATION;

        m_scrollSpeed += acceleration * dt;
        if (m_scrollSpeed > maxSpeed)
            m_scrollSpeed = maxSpeed;
    }

    m_player->update(dt);

    float viewLeft = getViewLeft();
    float viewRight = getViewRight();

    for (auto& obj : m_staticObjects)
        obj->update(dt);

    for (auto& obj : m_movingObjects) {
        if (auto missile = dynamic_cast<Missile*>(obj.get()))
            missile->update(dt, m_scrollSpeed);
        else
            obj->update(dt);
    }

    for (auto& obj : m_staticObjects)
        CollisionHandler::handle(*m_player, *obj);

    for (auto& obj : m_movingObjects)
        CollisionHandler::handle(*m_player, *obj);

    removeCollectedObjects();
    removeOffscreenObjects();

    if (!m_player->isDead()) {
        auto newStatic = m_spawnerManager.spawnStatic(dt, viewRight);
        for (auto& obj : newStatic)
            m_staticObjects.push_back(std::move(obj));

        auto newMoving = m_spawnerManager.spawnMoving(dt, viewRight);
        for (auto& obj : newMoving)
            m_movingObjects.push_back(std::move(obj));
    }

    m_staticObjects.erase(
        std::remove_if(m_staticObjects.begin(), m_staticObjects.end(),
            [viewLeft](const std::unique_ptr<StaticObject>& obj) {
                return obj->getPosition().x + obj->getSprite().getGlobalBounds().width < viewLeft;
            }),
        m_staticObjects.end()
    );

    m_player->anchorToViewLeft(viewLeft);
    m_statusBar.update(getViewRight() / GameConstants::DISTANCE_SCALING_FACTOR, 
                       m_player->getCollectedCoins(),
                       Resources::getInstance().getBestScore());
}

void Board::render() {
    m_window.setView(m_view);

    drawBackground();

    for (const auto& obj : m_staticObjects)
        obj->render(m_window);

    for (const auto& obj : m_movingObjects)
        obj->render(m_window);

    m_player->render(m_window);
    m_window.setView(m_window.getDefaultView());
    m_statusBar.render(m_window);

    for (const auto& btn : m_commandButtons)
        btn.render(m_window);
    m_window.setView(m_view);
}

void Board::handleEvent(const sf::Event& event) {
    m_player->handleEvents(event);

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f pos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
        for (auto& btn : m_commandButtons) {
            if (btn.contains(pos)) {
                if (auto cmd = btn.releaseCommand()) {
                    cmd->execute();
                    break;
                }
            }
        }
    }
}

bool Board::isGameOver() const {
    return m_player && m_player->isGameOverRequested();
}

void Board::scrollView(float dt) {
    m_view.move(m_scrollSpeed * dt, 0.f);
}

void Board::drawBackground() {
    float viewLeft = getViewLeft();

    float backgroundHeight = static_cast<float>(m_backgroundTexture->getSize().y);
    float scaleY = m_window.getSize().y / backgroundHeight;

    float introWidth = 0.f;

    if (m_introBackgroundTexture) {
        introWidth = static_cast<float>(m_introBackgroundTexture->getSize().x);
        float introHeight = static_cast<float>(m_introBackgroundTexture->getSize().y);

        float introScaleX = static_cast<float>(m_window.getSize().x) / introWidth;
        float introScaleY = static_cast<float>(m_window.getSize().y) / introHeight;

        m_introBackgroundSprite.setScale(introScaleX, introScaleY);
    }

    m_backgroundSprite.setScale(1.0f, scaleY);
    float backgroundWidth = static_cast<float>(m_backgroundTexture->getSize().x);

    int extraTiles = static_cast<int>(std::ceil(std::abs(m_scrollSpeed) / backgroundWidth)) +
                                      GameConstants::EXTRA_BACKGROUND_TILES;
    int tilesToDraw = static_cast<int>(std::ceil(m_view.getSize().x / backgroundWidth)) + extraTiles;

    int firstTileIndex = static_cast<int>((viewLeft - introWidth) / backgroundWidth) - 1;

    for (int i = 0; i < tilesToDraw; ++i) {
        float x = introWidth + (firstTileIndex + i) * backgroundWidth;

        if (x + backgroundWidth < viewLeft) continue;
        if (x >= -backgroundWidth) {
            m_backgroundSprite.setPosition(x, 0.f);
            m_window.draw(m_backgroundSprite);
        }
    }

    if (m_introBackgroundTexture && 
        viewLeft < introWidth + GameConstants::INTRO_BACKGROUND_FADEOUT_X) {
        m_introBackgroundSprite.setPosition(0.f, 0.f);
        m_window.draw(m_introBackgroundSprite);
    }
}

void Board::removeCollectedObjects() {
    m_staticObjects.erase(
        std::remove_if(m_staticObjects.begin(), m_staticObjects.end(),
            [](const auto& obj) {
                return obj->isMarkedForDeletion();
            }),
        m_staticObjects.end());

    m_movingObjects.erase(
        std::remove_if(m_movingObjects.begin(), m_movingObjects.end(),
            [](const auto& obj) {
                return obj->isMarkedForDeletion();
            }),
        m_movingObjects.end());
}

void Board::removeOffscreenObjects() {
    float viewLeft = getViewLeft();
    m_staticObjects.erase(
        std::remove_if(m_staticObjects.begin(), m_staticObjects.end(),
            [viewLeft](const auto& obj) {
                return obj->getPosition().x + obj->getSprite().getGlobalBounds().width < viewLeft;
            }),
        m_staticObjects.end());
}

float Board::getViewLeft() const {
    return m_view.getCenter().x - m_view.getSize().x / 2.f;
}

float Board::getViewRight() const {
    return m_view.getCenter().x + m_view.getSize().x / 2.f;
}

float Board::getScrollSpeed() const {
    return m_scrollSpeed;
}

void Board::setScrollSpeed(float speed) {
    m_scrollSpeed = speed;
}

float Board::getDistance() const {
    return getViewRight() / GameConstants::DISTANCE_SCALING_FACTOR;
}

void Board::addCommandButton(const std::string& textureName, sf::Vector2f position, std::unique_ptr<Command> cmd) {
    MenuButton btn(textureName, std::move(cmd));
    btn.setPosition(position.x, position.y);
    btn.setScale(GameConstants::COMMAND_BUTTON_SCALE, GameConstants::COMMAND_BUTTON_SCALE);
    m_commandButtons.push_back(std::move(btn));
}
