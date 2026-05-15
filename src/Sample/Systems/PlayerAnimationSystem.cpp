#include "PlayerAnimationSystem.h"

void PlayerAnimationSystem::OnInit()
{}

void PlayerAnimationSystem::OnUpdate()
{
    for (auto ent : _player)
    {
        auto& anim = _animationComponents.Get(ent);
        auto& mov = _movementComponents.Get(ent);
        if (anim.CurrentAnimation != AssetNames::RunAnim && (mov.Direction.x < 0 || mov.Direction.x > 0))
        {
            anim.CurrentAnimation = AssetNames::RunAnim;
        }
        else if (anim.CurrentAnimation != AssetNames::IdleAnim && mov.Direction.x == 0)
        {
            anim.CurrentAnimation = AssetNames::IdleAnim;
        }
    }
}
