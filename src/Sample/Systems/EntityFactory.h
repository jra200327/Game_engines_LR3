#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <SFML/Graphics.hpp>

#include "../../Ecs/World/World.h"
#include "../../Ecs/ReadConfig/ReadConfig.h"

enum class EntityType
{
    Player,
    Asteroid,
    Bullet
};

class EntityFactory  {
    
   World &_world;
   sf::Texture &_texture;

   float _minSize;
   float _maxSize;
   float _minSpeed;
   float _maxSpeed;
   float _offset;

   float _shootSpeed;

public:
    EntityFactory (World &wrld, sf::Texture &tex, const AsteroidConfig astCfg, const ShooterConfig shootCfg)
        : _world(wrld), _texture(tex), _minSize(astCfg.minSize), _maxSize(astCfg.maxSize), _minSpeed(astCfg.minSpeed), _maxSpeed(astCfg.maxSpeed), _offset(astCfg.offset), _shootSpeed(shootCfg.cd)
    {
    }

    void CreateEntity(EntityType type, sf::Vector2f pos);

    float RandomFloat(float min, float max);

    float& GetMinSpeed();
    float& GetMaxSpeed();
};

#endif //ENTITYFACTORY_H