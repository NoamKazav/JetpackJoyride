#pragma once

#include <unordered_map>
#include <typeindex>
#include "Objects/GameObject.h"
#include "Objects/Player.h"
#include "Objects/Coin.h"
#include "Utils/HashUtils.h"
#include "GameCore/Resources.h"
#include "Objects/Laser.h"
#include "Objects/Missile.h"
#include "Objects/Gift.h"

class CollisionHandler {
public:
    static void handle(Player& player, GameObject& obj);

private:
    using TypePair = std::pair<std::type_index, std::type_index>;
    using HitFunctionPtr = void(*)(GameObject&, GameObject&);
    using HitMap = std::unordered_map<TypePair, HitFunctionPtr, 
                        pair_hash<std::type_index, std::type_index>>;

    static HitMap initializeCollisionMap();
    static HitFunctionPtr lookup(const std::type_index& a, const std::type_index& b);
};



