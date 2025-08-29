#include "state/CommonWalkingState.h"
#include "Objects/Player.h"

void CommonWalkingState::enter(Player& player) {
    player.setVelocityY(0);
    player.setAnimation(getAnimationName());
}

