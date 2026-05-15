#ifndef GROUNDEDRESETSYSTEM_H
#define GROUNDEDRESETSYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/GravityComponent.h"

class GroundedResetSystem final : public ISystem
{
    ComponentStorage<GravityComponent>& _gravityComponents;

    Filter _gravityEntities;

public:
    GroundedResetSystem(World& world)
        : ISystem(world),
          _gravityComponents(world.GetStorage<GravityComponent>()),
          _gravityEntities(FilterBuilder(world)
              .With<GravityComponent>()
              .Build())
    {
    }

    void OnInit() override;
    void OnUpdate() override;
};

#endif // GROUNDEDRESETSYSTEM_H