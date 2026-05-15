#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/ShooterComponent.h"
#include "../Components/SpriteComponent.h"

#include "../../GameEngine/Input/InputManager.h"

class MovementSystem final : public ISystem {
    ComponentStorage<PositionComponent>& _positionComponents;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<SpriteComponent>& _spriteComponents;

    Filter _moveables;
    Filter _player;

    std::unordered_map<std::string, std::shared_ptr<InputAction>>& _actions;

    void Print(int ent);  // Это тоже можно вынести в отдельную систему

public:
    MovementSystem(World &world, std::unordered_map<std::string, std::shared_ptr<InputAction>>& actions)
        : ISystem(world),
            _actions(actions),
            _positionComponents(world.GetStorage<PositionComponent>()),
            _movementComponents(world.GetStorage<MovementComponent>()),
            _spriteComponents(world.GetStorage<SpriteComponent>()),
            _player(FilterBuilder(world)
                .With<PositionComponent>()
                .With<MovementComponent>()
                .With<ShooterComponent>()
                .Build()),
            _moveables(FilterBuilder(world)
                .With<PositionComponent>()
                .With<MovementComponent>()
                .Build())
    {
    }

    void OnInit() override;

    void OnUpdate() override;
};

#endif //MOVEMENTSYSTEM_H
