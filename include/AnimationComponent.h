#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <Objects/GameObject.h>
class AnimationComponent {
public:
    void setFrames(const std::vector<sf::IntRect>* frames);
    void update(float dt, GameObject& obj);
    void setPlayOnce(bool once) { m_playOnce = once; }
    bool isFinished() const { return m_finished; }

private:
    bool m_playOnce = false;
    bool m_finished = false;
    const std::vector<sf::IntRect>* m_frames = nullptr;
    float m_timeAccumulator = 0.f;
    int m_currentFrame = 0;
};
