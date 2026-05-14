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
#include "../Components/CameraComponent.h"
#include "../Components/DefaultCameraTag.h"
#include "../Components/FollowXCameraTag.h"
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


        positionsStorage.Add(asteroid, PositionComponent(pos.x, pos.y));
        collisionStorage.Add(asteroid, CollisionComponent());
        asteroidStorage.Add(asteroid, AsteroidComponent());
    }
    else if(type == EntityType::DefaultCamera)
    {
        int camera = _world.CreateEntity();
        auto& cameraStorage = _world.GetStorage<CameraComponent>();
        auto& defaultCameraStorage = _world.GetStorage<DefaultCameraTag>();
        cameraStorage.Add(camera, CameraComponent(sf::View(sf::FloatRect({0.f, 0.f}, {pos.x, pos.y}))));
        defaultCameraStorage.Add(camera, DefaultCameraTag());
    }
}