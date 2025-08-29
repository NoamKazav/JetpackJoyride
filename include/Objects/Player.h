#pragma once
#include "MovingObject.h"
#include "state/PlayerState.h"
#include <memory>
#include "Utils/GameConstants.h"
#include "state/DeadState.h"
#include "AnimationComponent.h"
#include "GiftEffects/GiftEffect.h"
#include <vector>


class Player : public MovingObject {
public:
    Player();
    void addEffectTimer(std::shared_ptr<GiftEffect> effect, float duration) {
        m_activeEffects.push_back({ effect, duration });
    }
    void move(float dx, float dy) override;
    void handleEvents(const sf::Event& event);
    void update(float dt) override;
    void render(sf::RenderWindow& window) const override;

    void setState(std::unique_ptr<PlayerState> newState);

    void setTextureRect(const sf::IntRect& rect);  
    void anchorToViewLeft(float viewLeftX);
    void clampToGround(float groundY);
    float getVelocityY() const { return m_velocityY; }
    void setVelocityY(float vy) { m_velocityY = vy; }
    void setAnimation(const std::string& animationName);
    void clampBottomToGround(float groundY);
    void increaseVelocityY(float delta) { m_velocityY += delta; }

    PlayerState* getState() const {
        return m_state.get();
    }

    void trackOrRefreshEffect(std::shared_ptr<GiftEffect> effect, float duration);

    bool isGameOverRequested() const;
    void requestGameOver();
    float getBottom() const;
    bool isDead() const;
    AnimationComponent& getAnimation();
    const AnimationComponent& getAnimation() const;

    void collectCoin();
    int getCollectedCoins() const;
    bool hasActiveEffect() const;
    void clearAllEffects();
    bool isInvincible() const;
    void setInvincibleFor(float seconds);

private:
    std::unique_ptr<PlayerState> m_state;
    AnimationComponent m_animation;
    float m_velocityY = 0.f;
    static bool m_registerit;
    bool m_gameOverRequested = false;
    int m_collectedCoins = 0;

    struct ActiveEffect {
        std::shared_ptr<GiftEffect> effect;
        float timeRemaining;
    };
    std::vector<ActiveEffect> m_activeEffects;
    float m_invincibleTime = 0.f;
};
