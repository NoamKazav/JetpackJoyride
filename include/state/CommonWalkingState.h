#pragma once
#include "state/PlayerState.h"
class Player;


class CommonWalkingState : public PlayerState {
public:
    void enter(Player& player) override;
    virtual std::string getAnimationName() const = 0;
};
