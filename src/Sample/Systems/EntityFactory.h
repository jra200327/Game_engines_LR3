#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <SFML/Graphics.hpp>

#include "../../Ecs/World/World.h"
#include "../../GameEngine/Assets/AssetManager.h"

enum class EntityType
{
    Player,
    Bullet,
    DefaultCamera,
    FollowXCamera,
    Tile,
    Tile1,
    BrickTile,
    QuestionTile,
    QuestionInactiveTile,
    PipeUpLeft,
    PipeUpRight,
    PipeLeft,
    PipeRight,
    BigHill,
    Finish
};

class EntityFactory  {
    
   World &_world;
   const AssetManager &_assets;

public:
    EntityFactory (World &wrld, const AssetManager& assets)
        : _world(wrld),
        _assets(assets)
    {
    }

    void CreateEntity(EntityType type, sf::Vector2f pos);
};

#endif //ENTITYFACTORY_H