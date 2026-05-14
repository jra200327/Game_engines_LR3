#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <SFML/Graphics.hpp>

#include "../../Ecs/World/World.h"
#include "../../Ecs/ReadConfig/ReadConfig.h"

enum class EntityType
{
    Player,
    Asteroid,
    Bullet,
    DefaultCamera,
    FollowXCamera
};

class EntityFactory  {
    
   World &_world;

public:
    EntityFactory (World &wrld)
        : _world(wrld)
    {
    }

    void CreateEntity(EntityType type, sf::Vector2f pos);
};

#endif //ENTITYFACTORY_H