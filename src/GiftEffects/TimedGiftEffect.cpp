#include "GiftEffects/TimedGiftEffect.h"
#include "Objects/Player.h"
#include "state/TankJettingState.h"
#include "state/TankWalkingState.h"
#include "state/TankFallingState.h"
#include "factory/GameFactory.h"
#include "Utils/GameConstants.h"
#include <iostream>

TimedGiftEffect::TimedGiftEffect(std::function<void(Player&)> onStart,
    std::function<void(Player&)> onEnd)
    : m_onStart(std::move(onStart)), m_onEnd(std::move(onEnd)) {
}

void TimedGiftEffect::apply(Player& player) {
    auto self = shared_from_this();
    m_player = &player;

    if (m_onStart)
        m_onStart(player);

    player.trackOrRefreshEffect(self, GameConstants::DEFAULT_GIFT_DURATION);
}

TimedGiftEffect::~TimedGiftEffect() {
    if (m_player && m_onEnd) {
        m_onEnd(*m_player);
    }
}
