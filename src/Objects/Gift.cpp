#include "Objects/Gift.h"
#include "GiftEffects/TimedGiftEffect.h"
#include "GiftEffects/ShieldEffect.h"
#include "GiftEffects/TankEffect.h"
#include "Objects/Player.h"
#include "GameCore/Resources.h"
#include "Utils/ObjectType.h"
#include <iostream>
#include "factory/GameFactory.h"


bool Gift::m_registerit = GameFactory<StaticObject, GiftType>::registerit(
    "Gift", [](GiftType&& gType) -> std::unique_ptr<StaticObject> {
        return std::make_unique<Gift>(std::move(gType));
    });

Gift::Gift(GiftType type) : m_type(type) {
    m_effect = generateEffect(type);
    setTexture(&Resources::getInstance().getObjectTexture(ObjectType::Gift));
}

void Gift::applyEffect(Player& player) {
    m_effect->apply(player);
}

std::shared_ptr<GiftEffect> Gift::generateEffect(GiftType type) {
    switch (type) {
    case GiftType::Tank:
        return std::make_shared<TimedGiftEffect>(
            TankEffect::onStart(),
            TankEffect::onEnd()
        );

    case GiftType::Shield:
        return std::make_shared<TimedGiftEffect>(
            ShieldEffect::onStart(),
            ShieldEffect::onEnd()
        );

    default:
        return std::make_shared<TimedGiftEffect>(
            TankEffect::onStart(),
            TankEffect::onEnd()
        );
    }
}