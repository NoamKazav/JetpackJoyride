#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Utils/GameConstants.h"
#include "GameCore/Resources.h"
#include "Utils/ObjectType.h"
#include "factory/GameFactory.h"
#include "Objects/GameObject.h"
#include "Objects/StaticObject.h"


class ObjectSpawner {
public:
    virtual ~ObjectSpawner() = default;
};