#include "state/CommonJettingState.h"

void CommonJettingState::enter(Player& player)  {
    player.setVelocityY(0.f);
    player.setAnimation(getAnimationName());
}