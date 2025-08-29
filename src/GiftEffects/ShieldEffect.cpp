#include "GiftEffects/ShieldEffect.h"

#include <iostream>
#include <stdexcept>
#include "Objects/Player.h"
#include "factory/GameFactory.h"

bool ShieldEffect::m_registerit = GameFactory<GiftEffect>::registerit("ShieldEffect", []() -> std::unique_ptr<GiftEffect> {
    return std::make_unique<ShieldEffect>();
    });

ShieldEffect::ShieldEffect()
    : TimedGiftEffect(
        [](Player& player) {
            player.setInvincibleFor(10.f);
        },
        [](Player& player) {
        }
    )
{}

std::function<void(Player&)> ShieldEffect::onStart() {
    return [](Player& player) {
        player.setInvincibleFor(10.f);
        };
}

std::function<void(Player&)> ShieldEffect::onEnd() {
    return [](Player& player) {
        };
}
