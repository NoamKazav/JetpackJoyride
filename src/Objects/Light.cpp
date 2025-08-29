#include "Objects/Light.h"
#include "GameCore/Resources.h"
#include "Utils/ObjectType.h"
#include "factory/GameFactory.h"

bool Light::m_registerit = GameFactory<StaticObject>::registerit(
    "Light", []() -> std::unique_ptr<StaticObject> {
        return std::make_unique<Light>();
    }
);

Light::Light() {
    const auto& tex = Resources::getInstance().getObjectTexture(ObjectType::Light);
    setTexture(&tex);

    m_frames = Resources::getInstance().getAnimationFrames("Light");
    if (!m_frames || m_frames->empty())
        throw std::runtime_error("Missing animation frames for 'Light'");

    setTextureRect((*m_frames)[0]);
}

void Light::update(float dt) {
    if (!m_frames || m_frames->empty()) return;

    m_timeAccumulator += dt;
    if (m_timeAccumulator >= 0.1f) {
        m_timeAccumulator = 0.f;
        m_currentFrame = (m_currentFrame + 1) % m_frames->size();
        setTextureRect((*m_frames)[m_currentFrame]);
    }
}
