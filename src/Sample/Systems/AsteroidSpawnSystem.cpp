#include "AsteroidSpawnSystem.h"
#include <random>


void AsteroidSpawnSystem::OnInit()
{

}

void AsteroidSpawnSystem::OnUpdate()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, _maxX);

    int value = dist(gen);

    if (_timer <= 0)
    {
        _factory.CreateEntity(EntityType::Asteroid, sf::Vector2f(value, -100));
        _timer = _spawnCd;
    }

    _timer--;
}

float& AsteroidSpawnSystem::GetCd()
{
    return _spawnCd;
}