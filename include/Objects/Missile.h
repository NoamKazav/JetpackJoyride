#pragma once
#include "Objects/MovingObject.h"
#include "AnimationComponent.h"
#include <memory>
#include "Utils/ObjectType.h"
#include "Objects/Player.h"

class MissileAnimationState;
class Player;
class Missile : public MovingObject {
public:
    Missile();
    void update(float dt, float scrollSpeed);
    void render(sf::RenderWindow& window) const override;
    void move(float dx, float dy) override;  

    void setState(std::unique_ptr<MissileAnimationState> newState);
    void setNewSprite(const std::string& animationName, ObjectType type);
    void animate(float dt);
    void setPositionByPlayer();
    void setWarningPosition(float viewRight, float y);
    void setPlayerRef(Player* player);
    float getPlayerY() const;
private:
    std::unique_ptr<MissileAnimationState> m_state;
    AnimationComponent m_animation;
    Player* m_player = nullptr;
    static bool m_registerit;
};


