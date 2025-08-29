#include "state/FireMissileState.h"
#include "Objects/Missile.h"
#include "GameCore/Resources.h"
#include "Utils/ObjectType.h"
#include "Utils/GameConstants.h"
#include "factory/GameFactory.h"

bool FireMissileState::m_registerit = GameFactory<MissileAnimationState, Missile&>::registerit(
    "FireMissileState",
    [](Missile& m) -> std::unique_ptr<MissileAnimationState> {
        return std::make_unique<FireMissileState>(&m);
    }
);

FireMissileState::FireMissileState(Missile* missile) {
    missile->setNewSprite("Missile", ObjectType::Missile);
    Resources::getInstance().playSound(SoundType::MissileLaunch);
}

void FireMissileState::update(Missile* missile, float dt, float scrollSpeed) {
    missile->move(-GameConstants::MISSILE_SPEED * dt, 0.f);
    missile->animate(dt);
}