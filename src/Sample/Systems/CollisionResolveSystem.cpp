#include "CollisionResolveSystem.h"
#include <vector>


void CollisionResolveSystem::OnInit()
{

}

void CollisionResolveSystem::OnUpdate()
{
    std::vector<int> toDestroy;
    for (auto ent : _collideables)
    {
        auto& collision = _collisionComponents.Get(ent);

        for (const auto& info : collision.Collisions)
        {
            int other = info.entity;
            CollisionSide side = info.side;

            if (!world.IsEntityAlive(ent) || !world.IsEntityAlive(other))
                continue;

            bool playerBulletCollision = (_shooterComponents.Has(ent) && _bulletComponents.Has(other)) ||
                (_bulletComponents.Has(ent) && _shooterComponents.Has(other));

            if (playerBulletCollision)
                continue;
            
            bool isPlayer = _shooterComponents.Has(ent);
            bool isWorld  = _boxColliderComponents.Has(other);

            if (!isPlayer || !isWorld)
                continue;

            auto& pos = _positionComponents.Get(ent);
            auto& box = _boxColliderComponents.Get(ent);

            auto& otherPos = _positionComponents.Get(other);
            auto& otherBox = _boxColliderComponents.Get(other);

            if (side == CollisionSide::Left)
            {
                pos.X = otherPos.X - box.Width;
            }
            else if (side == CollisionSide::Right)
            {
                pos.X = otherPos.X + otherBox.Width;
            }
            else if (side == CollisionSide::Top)
            {
                pos.Y = otherPos.Y - box.Height;
                if (_gravityComponents.Has(ent))
                {
                    auto& grav = _gravityComponents.Get(ent);
                    grav.grounded = true;
                    grav.currentVelocityY = 0; 
                }
            }
            else if (side == CollisionSide::Bottom)
            {
                pos.Y = otherPos.Y + otherBox.Height;
                if (_movementComponents.Has(ent))
                {
                    auto& mov = _movementComponents.Get(ent);
                    mov.Direction.y = 0;
                }
            }
        }
    }

    for (auto ent : toDestroy)
    {
        if (world.IsEntityAlive(ent))
        {
            std::cout << "Deleting " << ent << std::endl;
            world.RemoveEntity(ent);
            std::cout << "Deleted " << ent << std::endl;
        }
    }

}