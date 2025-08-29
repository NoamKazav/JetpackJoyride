#pragma once

#include "StaticObject.h"

class Light : public StaticObject {
public:
    Light();
    void update(float dt) override;

private:
    const std::vector<sf::IntRect>* m_frames = nullptr;
    int m_currentFrame = 0;
    float m_timeAccumulator = 0.f;

    static bool m_registerit;
};
