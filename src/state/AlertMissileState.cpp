#include "state/AlertMissileState.h"
#include "state/FireMissileState.h"
#include "Objects/Missile.h"
#include "GameCore/Resources.h"
#include "Utils/ObjectType.h"
#include <stdexcept>
#include "factory/GameFactory.h"

bool AlertMissileState::m_registerit = GameFactory<MissileAnimationState, Missile&>::registerit(
    "AlertMissileState",
    [](Missile& m) -> std::unique_ptr<MissileAnimationState> {
        return std::make_unique<AlertMissileState>(&m);
    }
);

AlertMissileState::AlertMissileState(Missile* missile) {
    if (!missile)
        throw std::invalid_argument("Null missile pointer in AlertMissileState constructor");

    missile->setNewSprite("FirstWarning", ObjectType::FirstAlert);
    Resources::getInstance().playSound(SoundType::MissileAlarm);
}

void AlertMissileState::update(Missile* missile, float dt, float scrollSpeed) {
    if (!missile)
        throw std::invalid_argument("Null missile pointer in AlertMissileState::update");

    m_timer += dt;

    float newX = missile->getPosition().x + scrollSpeed * dt;
    float newY = missile->getPosition().y;

    if (m_followY)
        newY = missile->getPlayerY();

    missile->setPosition({ newX, newY });
    missile->animate(dt);

    if (m_timer > GameConstants::MISSILE_SECOND_WARNING_TIME && m_firstTime) {
        missile->setNewSprite("SecondWarning", ObjectType::SecondAlert);
        m_firstTime = false;
        m_followY = false;
    }


    if (m_timer > GameConstants::MISSILE_FIRE_TIME) {
        missile->setState(GameFactory<MissileAnimationState, Missile&>::create("FireMissileState", *missile));
    }
}
