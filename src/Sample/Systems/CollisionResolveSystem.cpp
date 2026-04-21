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

        for (auto other : collision.CollisionEntities)
        {
            if (ent >= other) continue;
            bool isShooter1  = _shooterComponents.Has(ent);
            bool isAsteroid1 = _asteroidComponents.Has(ent);
            bool isBullet1   = _bulletComponents.Has(ent);

            bool isShooter2  = _shooterComponents.Has(other);
            bool isAsteroid2 = _asteroidComponents.Has(other);
            bool isBullet2   = _bulletComponents.Has(other);

            if ((isBullet1 && isAsteroid2) || (isBullet2 && isAsteroid1))
            {
                int bullet   = isBullet1 ? ent   : other;
                int asteroid = isAsteroid1 ? ent : other;

                toDestroy.push_back(bullet);
                toDestroy.push_back(asteroid);

                std::cout << "Bullet hit asteroid" << std::endl;
                _scoreManager.UpdateScore(100);
            }
            else if ((isShooter1 && isAsteroid2) || (isAsteroid1 && isShooter2))
            {
                int player = isShooter1 ? ent : other;
                int asteroid =  isAsteroid1 ? ent : other;

                std::cout << "Player died" << std::endl;

                _window.EndGame();
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