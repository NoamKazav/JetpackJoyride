#pragma once

#include "Objects/StaticObject.h"
#include "GiftEffects/GiftEffect.h"
#include "Utils/ObjectType.h"
#include <memory>

enum class GiftType;
class Player;

class Gift : public StaticObject {
public:
    Gift(GiftType type);
    void applyEffect(Player& player);

private:
    const std::vector<sf::IntRect>* m_frames = nullptr;
    float m_timeAccumulator = 0.f;
    int m_currentFrame = 0;
    std::shared_ptr<GiftEffect> m_effect;

    static bool m_registerit;
    GiftType m_type;

    std::shared_ptr<GiftEffect> generateEffect(GiftType type);
};
