#include "state/CommonFallingState.h"

void CommonFallingState::enter(Player& player)  {
    player.setVelocityY(0);
    player.setAnimation(getAnimationName());
}