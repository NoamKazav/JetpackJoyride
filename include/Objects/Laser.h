#pragma once
#include "StaticObject.h"
#include "AnimationComponent.h"
class Laser : public StaticObject {
public:
    Laser();
    void update(float dt) override;

    void render(sf::RenderWindow& window) const override {
        GameObject::render(window);  
    }
private:
    AnimationComponent m_animation;
};
