#pragma once
#include <functional>
#include "Objects/Player.h"
#include "GiftEffects/TimedGiftEffect.h"

class ShieldEffect : public TimedGiftEffect {
public:
    static std::function<void(Player&)> onStart();
    static std::function<void(Player&)> onEnd();
    ShieldEffect();  
private:
    static bool m_registerit;
};

