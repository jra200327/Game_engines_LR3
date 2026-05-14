#ifndef COLLISIONRESOLVESYSTEM_H
#define COLLISIONRESOLVESYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/CollisionComponent.h"
#include "../Components/ShooterComponent.h"
#include "../Components/AsteroidComponent.h"
#include "../Components/BulletComponent.h"

class CollisionResolveSystem final : public ISystem {
    
    ComponentStorage<CollisionComponent>& _collisionComponents;
    ComponentStorage<ShooterComponent>& _shooterComponents;
    ComponentStorage<AsteroidComponent>& _asteroidComponents;
    ComponentStorage<BulletComponent>& _bulletComponents;

    Filter _collideables;

public:
    CollisionResolveSystem(World &world)
        : ISystem(world),
            _collisionComponents(world.GetStorage<CollisionComponent>()),
            _shooterComponents(world.GetStorage<ShooterComponent>()),
            _asteroidComponents(world.GetStorage<AsteroidComponent>()),
            _bulletComponents(world.GetStorage<BulletComponent>()),
            _collideables(FilterBuilder(world)
                .With<CollisionComponent>()
                .Build())
    {
    }

    void OnInit() override;

    void OnUpdate() override;
};

#endif //COLLISIONRESOLVESYSTEM_H