#include "EntityFactory.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ShooterComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/AsteroidComponent.h"
#include <random>

void EntityFactory::CreateEntity(EntityType type, sf::Vector2f pos)
{
    if (type == EntityType::Player)
    {
        const int player1 = _world.CreateEntity();
        auto& positionsStorage = _world.GetStorage<PositionComponent>();
        auto& movementsStorage = _world.GetStorage<MovementComponent>();
        auto& boxColliderStorage = _world.GetStorage<BoxColliderComponent>();
        auto& collisionStorage = _world.GetStorage<CollisionComponent>();
        auto& spriteStorage = _world.GetStorage<SpriteComponent>();
        auto& shooterStorage = _world.GetStorage<ShooterComponent>();

        positionsStorage.Add(player1, PositionComponent(pos.x, pos.y));
        movementsStorage.Add(player1, MovementComponent(10, sf::Vector2f(0, 0)));
        boxColliderStorage.Add(player1, BoxColliderComponent(24, 86));
        collisionStorage.Add(player1, CollisionComponent());
        spriteStorage.Add(player1, SpriteComponent(sf::Vector2i(48, 32), sf::Vector2i(96, 128), _texture, -90, 2));
        shooterStorage.Add(player1, ShooterComponent(_shootSpeed));
    }
    else if(type == EntityType::Bullet)
    {
        const int bullet = _world.CreateEntity();
        auto& positionsStorage = _world.GetStorage<PositionComponent>();
        auto& movementsStorage = _world.GetStorage<MovementComponent>();
        auto& boxColliderStorage = _world.GetStorage<BoxColliderComponent>();
        auto& collisionStorage = _world.GetStorage<CollisionComponent>();
        auto& spriteStorage = _world.GetStorage<SpriteComponent>();
        auto& bulletStorage = _world.GetStorage<BulletComponent>();

        positionsStorage.Add(bullet, PositionComponent(pos.x, pos.y));
        movementsStorage.Add(bullet, MovementComponent(50, sf::Vector2f(0, -1)));
        boxColliderStorage.Add(bullet, BoxColliderComponent(8, 8));
        collisionStorage.Add(bullet, CollisionComponent());
        spriteStorage.Add(bullet, SpriteComponent(sf::Vector2i(16, 16), sf::Vector2i(224, 144), _texture, -90, 2));
        bulletStorage.Add(bullet, BulletComponent());
    }
    else if(type == EntityType::Asteroid)
    {
        const int asteroid = _world.CreateEntity();
        auto& positionsStorage = _world.GetStorage<PositionComponent>();
        auto& movementsStorage = _world.GetStorage<MovementComponent>();
        auto& circleColliderStorage = _world.GetStorage<CircleColliderComponent>();
        auto& collisionStorage = _world.GetStorage<CollisionComponent>();
        auto& spriteStorage = _world.GetStorage<SpriteComponent>();
        auto& asteroidStorage = _world.GetStorage<AsteroidComponent>();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, 2);

        int value = dist(gen);

        sf::Vector2i atlPos = sf::Vector2i(0, 80);

        if (value == 1)
        {
            atlPos = sf::Vector2i(48, 80);
        }
        else if (value == 2)
        {
            atlPos = sf::Vector2i(96, 80);
        }

        float randomXDir = RandomFloat(-_offset, _offset);
        float randomSpeed = RandomFloat(_minSpeed, _maxSpeed);
        float randomSize = RandomFloat(_minSize, _maxSize);

        positionsStorage.Add(asteroid, PositionComponent(pos.x, pos.y));
        movementsStorage.Add(asteroid, MovementComponent(randomSpeed, sf::Vector2f(randomXDir, 1)));
        circleColliderStorage.Add(asteroid, CircleColliderComponent(randomSize*0.7*48));
        collisionStorage.Add(asteroid, CollisionComponent());
        spriteStorage.Add(asteroid, SpriteComponent(sf::Vector2i(48, 48), atlPos, _texture, 0, randomSize));
        asteroidStorage.Add(asteroid, AsteroidComponent());
    }
}

float EntityFactory::RandomFloat(float min, float max)
{
    if (max > min)
    {
        std::random_device rng;
        std::mt19937 gen(rng());
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }
    else
    {
        return max;
    }
}

float& EntityFactory::GetMinSpeed()
{
    return _minSpeed;
}

float& EntityFactory::GetMaxSpeed()
{
    return _maxSpeed;
}