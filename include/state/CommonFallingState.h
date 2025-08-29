#pragma once
#include "state/PlayerState.h"
#include "Objects/Player.h"

class CommonFallingState : public PlayerState {
public:
    void enter(Player& player) override;
    virtual std::string getAnimationName() const = 0;
};
