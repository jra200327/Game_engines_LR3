#include "ShootingSystem.h"

void ShootingSystem::OnInit()
{

}

void ShootingSystem::OnUpdate()
{
    for (const auto eventEntity : _shootInputEvents)
    {
        for (const auto ent : _shooter)
        {
            auto& position = _positionComponents.Get(ent);
            auto& shoot = _shooterComponents.Get(ent);

            if(shoot.timer <= 0)
            {
                _factory.CreateEntity(EntityType::Bullet, sf::Vector2f(position.X, position.Y));
                shoot.timer = shoot.cd;
                std::cout << "Pew" << std::endl;;
            }
            
        }

        world.RemoveEntity(eventEntity);
    }

    for (const auto ent : _shooter)
    {
        auto& shoot = _shooterComponents.Get(ent);
        shoot.timer--;
    }
}