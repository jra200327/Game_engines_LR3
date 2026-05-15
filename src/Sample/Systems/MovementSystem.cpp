#include "MovementSystem.h"

void MovementSystem::Print(int ent)
{
    auto& position = _positionComponents.Get(ent);

    std::cout << ent << " Pos: " << position.X << ", " << position.Y << std::endl;
}

void MovementSystem::OnInit()
{

}

void MovementSystem::OnUpdate()
{
        for (const auto ent : _player)
        {
            auto& movement = _movementComponents.Get(ent);
            auto& sprite = _spriteComponents.Get(ent);

            movement.Direction.x = 0.f;

            if (_actions["move_left"]->Type() == ActionType::Start)
            {
                movement.Direction.x -= 1.f;
                sprite.flipped = true;
            }

            if (_actions["move_right"]->Type() == ActionType::Start)
            {
                movement.Direction.x += 1.f;
                sprite.flipped = false;
            }
            if (_actions["jump"]->Type() == ActionType::Start)
            {
            }
        }

        for (const auto ent : _moveables)
        {
            auto& position = _positionComponents.Get(ent);
            auto& movement = _movementComponents.Get(ent);
            position.X += movement.Speed * movement.Direction.x;
            position.Y += movement.Speed * movement.Direction.y;
        }
}
