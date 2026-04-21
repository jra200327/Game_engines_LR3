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
            auto& position = _positionComponents.Get(ent);
            auto& movement = _movementComponents.Get(ent);

            if(!(_moveInputEvents.begin()==_moveInputEvents.end()))
            {
                for (const auto eventEntity : _moveInputEvents)
                {
                    auto& event = _moveInputEventComponents.Get(eventEntity);

                    if(event.Direction == MoveDirection::Right)
                    {
                        movement.Direction.x = -1;
                    }
                    else if (event.Direction == MoveDirection::Left)
                    {
                        movement.Direction.x = 1;
                    }

                    world.RemoveEntity(eventEntity);
                }
            }
            else 
            {
                movement.Direction.x = 0;
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
