#pragma once

#include <functional>
#include "GiftEffects/TimedGiftEffect.h"
class Player;

class TankEffect: public TimedGiftEffect {
public:
    static std::function<void(Player&)> onStart();
    static std::function<void(Player&)> onEnd();
    TankEffect();

private:
    static bool m_registerit;
};
