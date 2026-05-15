#ifndef COLLISIONRESOLVESYSTEM_H
#define COLLISIONRESOLVESYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/CollisionComponent.h"
#include "../Components/ShooterComponent.h"
#include "../Components/AsteroidComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/GravityComponent.h"
#include "../Components/MovementComponent.h"

class CollisionResolveSystem final : public ISystem {
    
    ComponentStorage<CollisionComponent>& _collisionComponents;
    ComponentStorage<ShooterComponent>& _shooterComponents;
    ComponentStorage<AsteroidComponent>& _asteroidComponents;
    ComponentStorage<BulletComponent>& _bulletComponents;
    ComponentStorage<BoxColliderComponent>& _boxColliderComponents;
    ComponentStorage<PositionComponent>& _positionComponents;
    ComponentStorage<GravityComponent>& _gravityComponents;
    ComponentStorage<MovementComponent>& _movementComponents;

    Filter _collideables;

public:
    CollisionResolveSystem(World &world)
        : ISystem(world),
            _collisionComponents(world.GetStorage<CollisionComponent>()),
            _shooterComponents(world.GetStorage<ShooterComponent>()),
            _asteroidComponents(world.GetStorage<AsteroidComponent>()),
            _bulletComponents(world.GetStorage<BulletComponent>()),
            _boxColliderComponents(world.GetStorage<BoxColliderComponent>()),
            _positionComponents(world.GetStorage<PositionComponent>()),
            _gravityComponents(world.GetStorage<GravityComponent>()),
            _movementComponents(world.GetStorage<MovementComponent>()),
            _collideables(FilterBuilder(world)
                .With<CollisionComponent>()
                .Build())
    {
    }

    void OnInit() override;

    void OnUpdate() override;
};

#endif //COLLISIONRESOLVESYSTEM_H