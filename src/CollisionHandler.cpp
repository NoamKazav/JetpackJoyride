#include "CollisionHandler.h"
#include <iostream>
#include "factory/GameFactory.h"


void handlePlayerHit(Player& player, SoundType soundType) {
    if (player.isDead())
        return;

    if (player.hasActiveEffect()) {
        player.clearAllEffects();
        Resources::getInstance().playSound(soundType);
        return;
    }
    Resources::getInstance().playSound(soundType);
    if (player.isInvincible())
        return;

    auto newState = GameFactory<PlayerState>::create("Dead");
    if (!newState)
        throw std::runtime_error("Failed to create Dead state for Player");

    player.setState(std::move(newState));
} 


void handlePlayerHitsCoin(GameObject& obj1, GameObject& obj2) {
    auto& player = static_cast<Player&>(obj1);
    auto& coin = static_cast<Coin&>(obj2);

    coin.setCollected();
    player.collectCoin(); 

    Resources::getInstance().playSound(SoundType::Coin);
}


void handlePlayerHitsLaser(GameObject& obj1, GameObject& obj2) {
    auto& player = static_cast<Player&>(obj1);
    if (player.isInvincible())
    {
        return;
    }
    handlePlayerHit(player, SoundType::LaserHit);
}

void handlePlayerHitsMissile(GameObject& obj1, GameObject& obj2) {
    auto& player = static_cast<Player&>(obj1);
    auto& missile = static_cast<Missile&>(obj2);

    handlePlayerHit(player, SoundType::MissileHit);
    missile.markForDeletion();

    if (!player.isDead()) return; 
}

void handlePlayerHitsGift(GameObject& obj1, GameObject& obj2) {
    auto& player = static_cast<Player&>(obj1);
    auto& gift = static_cast<Gift&>(obj2);

    if (player.isDead())
        return;

    gift.applyEffect(player);
    Resources::getInstance().playSound(SoundType::Power);
    gift.markForDeletion();
}


CollisionHandler::HitMap CollisionHandler::initializeCollisionMap() {
    HitMap map;
    map[{typeid(Player), typeid(Coin)}] = &handlePlayerHitsCoin;
    map[{typeid(Coin), typeid(Player)}] = [](GameObject& a, GameObject& b) {
        handlePlayerHitsCoin(b, a);
        };
    map[{typeid(Player), typeid(Laser)}] = &handlePlayerHitsLaser;
    map[{typeid(Laser), typeid(Player)}] = [](GameObject& a, GameObject& b) {
        handlePlayerHitsLaser(b, a);
        };
    map[{typeid(Player), typeid(Missile)}] = &handlePlayerHitsMissile;
    map[{typeid(Missile), typeid(Player)}] = [](GameObject& a, GameObject& b) {
        handlePlayerHitsMissile(b, a);
        };
    map[{typeid(Player), typeid(Gift)}] = &handlePlayerHitsGift;
    map[{typeid(Gift), typeid(Player)}] = [](GameObject& a, GameObject& b) {
        handlePlayerHitsGift(b, a);
        };
    return map;
}

CollisionHandler::HitFunctionPtr CollisionHandler::lookup(const std::type_index& a, const std::type_index& b) {
    static HitMap map = initializeCollisionMap();

    auto it = map.find({ a, b });
    if (it != map.end())
        return it->second;

    return [](GameObject&, GameObject&) {};  
}

void CollisionHandler::handle(Player& player, GameObject& obj) {
    if (!player.getBounds().intersects(obj.getBounds()))
        return;

    auto func = lookup(typeid(player), typeid(obj));
    func(player, obj);
}

