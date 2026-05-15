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
        spriteStorage.Add(player1, SpriteComponent({24, 24}, {0, 0}, _assets.GetTexture(AssetNames::TexRun), 0.f, 2.f));
        shooterStorage.Add(player1, ShooterComponent(1));
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
     else if (type == EntityType::Tile)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({64, 64}, {0, 0}, _assets.GetTexture(AssetNames::Tile), 0.f, 1.f));
    }
    else if (type == EntityType::Tile1)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({64, 64}, {0, 0}, _assets.GetTexture(AssetNames::Tile1), 0.f, 1.f));
    }
    else if (type == EntityType::BrickTile)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({64, 64}, {0, 0}, _assets.GetTexture(AssetNames::Brick_Tile), 0.f, 1.f));
    }
    else if (type == EntityType::QuestionTile)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({64, 64}, {0, 0}, _assets.GetTexture(AssetNames::Question_Tile), 0.f, 1.f));
    }
    else if (type == EntityType::QuestionInactiveTile)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({64, 64}, {0, 0}, _assets.GetTexture(AssetNames::Question_Inactive_Tile), 0.f, 1.f));
    }
    else if (type == EntityType::PipeUpLeft)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({64, 64}, {0, 0}, _assets.GetTexture(AssetNames::Pipe_Up_L), 0.f, 1.f));
    }
    else if (type == EntityType::PipeUpRight)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({64, 64}, {0, 0}, _assets.GetTexture(AssetNames::Pipe_Up_R), 0.f, 1.f));
    }
    else if (type == EntityType::PipeLeft)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({64, 64}, {0, 0}, _assets.GetTexture(AssetNames::Pipe_L), 0.f, 1.f));
    }
    else if (type == EntityType::PipeRight)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({64, 64}, {0, 0}, _assets.GetTexture(AssetNames::Pipe_R), 0.f, 1.f));
    }
    else if (type == EntityType::BigHill)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({320, 192}, {0, 0}, _assets.GetTexture(AssetNames::BigHill), 0.f, 1.f));
    }
    else if (type == EntityType::Finish)
    {
        int e = _world.CreateEntity();
        auto& p = _world.GetStorage<PositionComponent>();
        auto& s = _world.GetStorage<SpriteComponent>();

        p.Add(e, PositionComponent(pos.x, pos.y));
        s.Add(e, SpriteComponent({64, 128}, {0, 0}, _assets.GetTexture(AssetNames::Finish), 0.f, 1.f));
    }
    else if (type == EntityType::DefaultCamera)
    {
        int e = _world.CreateEntity();
        auto& cam = _world.GetStorage<CameraComponent>();
        auto& tag = _world.GetStorage<DefaultCameraTag>();

        cam.Add(e, CameraComponent(sf::View(sf::FloatRect({0.f, 0.f}, {pos.x, pos.y}))));
        tag.Add(e, DefaultCameraTag());
    }
    else if (type == EntityType::FollowXCamera)
    {
        int e = _world.CreateEntity();
        auto& cam = _world.GetStorage<CameraComponent>();
        auto& tag = _world.GetStorage<FollowXCameraTag>();

        cam.Add(e, CameraComponent(sf::View(sf::FloatRect({0.f, 0.f}, {pos.x, pos.y}))));
        tag.Add(e, FollowXCameraTag());
    }
}