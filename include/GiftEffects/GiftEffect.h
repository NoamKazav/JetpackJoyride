#pragma once

class Player;

class GiftEffect {
public:
    virtual ~GiftEffect() = default;
    virtual void apply(Player& player) = 0;
};

