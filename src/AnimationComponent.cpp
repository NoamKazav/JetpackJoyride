#include "AnimationComponent.h"
#include <stdexcept>

void AnimationComponent::setFrames(const std::vector<sf::IntRect>* frames) {
    m_frames = frames;
    m_timeAccumulator = 0.f;
    m_currentFrame = 0;
}

void AnimationComponent::update(float dt, GameObject& obj) {
    if (!m_frames || m_frames->empty())
        throw std::runtime_error("AnimationComponent::update - missing or empty frame list");

    if (m_playOnce && m_currentFrame + 1 >= m_frames->size()) {
        m_finished = true;
        return;
    }

    m_timeAccumulator += dt;
    if (m_timeAccumulator >= 0.1f) {
        m_timeAccumulator = 0.f;
        m_currentFrame = (m_currentFrame + 1) % m_frames->size();
        obj.setCurrentFrame((*m_frames)[m_currentFrame]);
    }
}
