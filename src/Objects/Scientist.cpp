#include "Objects/Scientist.h"
#include "GameCore/Resources.h"
#include "Utils/ObjectType.h"
#include "Utils/GameConstants.h"
#include "factory/GameFactory.h"

bool registerScientist = GameFactory<MovingObject>::registerit("Scientist", []() -> std::unique_ptr<MovingObject> {
    return std::make_unique<Scientist>();
    });

Scientist::Scientist() {
    const auto& tex = Resources::getInstance().getObjectTexture(ObjectType::Scientists);
    setTexture(&tex);

    const auto* frames = Resources::getInstance().getAnimationFrames("Scientists");
    if (!frames || frames->empty())
        throw std::runtime_error("Missing animation frames for 'Scientists'");

    setTextureRect((*frames)[0]);
    m_animation.setFrames(frames);

    m_velocity = GameConstants::SCIENTIST_VELOCITY_RIGHT;

}
void Scientist::move(float dx, float dy) {
    setPosition({ getPosition().x + dx, getPosition().y + dy });
}

void Scientist::update(float dt) {
    move(m_velocity.x * dt, m_velocity.y * dt);
    m_animation.update(dt, *this);
}
