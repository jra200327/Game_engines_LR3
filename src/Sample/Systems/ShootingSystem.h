#ifndef SHOOTINGSYSTEM_H
#define SHOOTINGSYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/ShooterComponent.h"
#include "../Components/ShootEvent.h"
#include "EntityFactory.h"

class ShootingSystem final : public ISystem {
    ComponentStorage<PositionComponent>& _positionComponents;
    ComponentStorage<ShooterComponent>& _shooterComponents;

    Filter _shooter;
    Filter _shootInputEvents;
    
    EntityFactory &_factory;

public:
    ShootingSystem(World &world, EntityFactory &factory)
        : ISystem(world),
            _factory(factory),
            _positionComponents(world.GetStorage<PositionComponent>()),
            _shooterComponents(world.GetStorage<ShooterComponent>()),
            _shooter(FilterBuilder(world)
                .With<ShooterComponent>()
                .With<PositionComponent>()
                .Build()),
            _shootInputEvents(FilterBuilder(world)
                .With<ShootEvent>()
                .Build())
    {
    }

    void OnInit() override;

    void OnUpdate() override;
};

#endif //SHOOTINGSYSTEM_H