#include "GiftEffects/TankEffect.h"
#include "Objects/Player.h"
#include "factory/GameFactory.h"
#include "state/TankJettingState.h"
#include "state/TankFallingState.h"
#include "state/TankWalkingState.h"
#include "state/JettingState.h"
#include "state/FallingState.h"
#include "state/WalkingState.h"
#include "factory/GameFactory.h"

bool TankEffect::m_registerit = GameFactory<GiftEffect>::registerit("TankEffect", []() -> std::unique_ptr<GiftEffect> {
    return std::make_unique<TankEffect>();
    });

TankEffect::TankEffect()
    : TimedGiftEffect(
        [](Player& player) {
            player.setInvincibleFor(10.f);
        },
        [](Player& player) {
        }
    )
{}

std::function<void(Player&)> TankEffect::onStart() {
    return [](Player& player) {
        player.setState(GameFactory<PlayerState>::create("TankJetting"));
        };
}

std::function<void(Player&)> TankEffect::onEnd() {
    return [](Player& player) {
        auto* state = player.getState();

        if (dynamic_cast<TankJettingState*>(state))
            player.setState(GameFactory<PlayerState>::create("Jetting"));
        else if (dynamic_cast<TankFallingState*>(state))
            player.setState(GameFactory<PlayerState>::create("Falling"));
        else if (dynamic_cast<TankWalkingState*>(state))
            player.setState(GameFactory<PlayerState>::create("Walking"));
        };
}
