#include "Objects/Coin.h"
#include "GameCore/Resources.h"
#include "Utils/ObjectType.h"
#include "factory/GameFactory.h"
#include <stdexcept>

bool registerCoin = GameFactory<StaticObject>::registerit("Coin", []() -> std::unique_ptr<StaticObject> {
    return std::make_unique<Coin>();
    });

Coin::Coin() {
    setTexture(&Resources::getInstance().getObjectTexture(ObjectType::Coin));

    const auto* frames = Resources::getInstance().getAnimationFrames("coin");
    if (!frames || frames->empty())
        throw std::runtime_error("Missing animation frames for coin");

    setTextureRect((*frames)[0]);
    m_animation.setFrames(frames);
}

void Coin::update(float dt) {
    m_animation.update(dt, *this);
}
