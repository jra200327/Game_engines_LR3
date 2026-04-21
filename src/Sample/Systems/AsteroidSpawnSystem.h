#ifndef ASTEROIDSPAWNSYSTEM_H
#define ASTEROIDSPAWNSYSTEM_H

#include "../../Ecs/Systems/ISystem.h"

#include "../Systems/EntityFactory.h"

class AsteroidSpawnSystem final : public ISystem {
    //ASS for short
    EntityFactory& _factory;

    float _spawnCd;
    float _timer = 0;

    int _maxX;
public:
    AsteroidSpawnSystem(World &world, EntityFactory &factory, float spawnRate, int maxX)
        : ISystem(world),
            _factory(factory),
            _spawnCd(spawnRate),
            _maxX(maxX)
    {
    }

    void OnInit() override;

    void OnUpdate() override;

    float& GetCd();
};

#endif //ASTEROIDSPAWNSYSTEM_H