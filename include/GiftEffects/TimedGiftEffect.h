#pragma once

#include "GiftEffects/GiftEffect.h"
#include <functional>
#include <memory>

class Player;

class TimedGiftEffect : public GiftEffect, public std::enable_shared_from_this<TimedGiftEffect> {
public:
    TimedGiftEffect(std::function<void(Player&)> onStart,
        std::function<void(Player&)> onEnd);

    void apply(Player& player);

    virtual ~TimedGiftEffect();

private:
    Player* m_player = nullptr;
    std::function<void(Player&)> m_onStart;
    std::function<void(Player&)> m_onEnd;
};
