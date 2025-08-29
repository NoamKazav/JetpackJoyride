#include "Objects/Laser.h"
#include "GameCore/Resources.h"
#include "Utils/ObjectType.h"
#include "factory/GameFactory.h"

bool registerLaser = GameFactory<StaticObject>::registerit("Laser", []() -> std::unique_ptr<StaticObject> {
    return std::make_unique<Laser>();
    });

Laser::Laser() {
    setTexture(&Resources::getInstance().getObjectTexture(ObjectType::Laser));
    const auto* frames = Resources::getInstance().getAnimationFrames("Laser");

    if (!frames || frames->empty())
        throw std::runtime_error("Missing animation frames for Laser");

    setTextureRect((*frames)[0]);
    m_animation.setFrames(frames);
}

void Laser::update(float dt) {
    m_animation.update(dt, *this);
}
