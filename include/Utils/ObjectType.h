#pragma once

#include <string>

enum class ObjectType {
    Scientists,
    Missile,
    Laser,
    Coin,
    Gravity,
    Light,
    Gift,
    Player,
    Tank,
    JetTank,
    FirstAlert,
    SecondAlert,
    Dead,
    Exhaust,
    Bubble,
    Intro
};

enum class SoundType {
    Coin,
    Power,
    MissileHit,
    MissileAlarm,
    MissileLaunch,
    LaserHit,
    ShieldSpeed,
    Explosion,
    Game
};

enum class GiftType {
    Tank,
    Shield
};
