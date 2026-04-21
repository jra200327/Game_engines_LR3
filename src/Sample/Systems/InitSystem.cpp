#include "InitSystem.h"

void InitSystem::OnInit()
{
    _factory.CreateEntity(EntityType::Player, sf::Vector2f(32, 680));
}