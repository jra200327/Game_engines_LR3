#include "GroundedResetSystem.h"

void GroundedResetSystem::OnInit()
{
}

void GroundedResetSystem::OnUpdate()
{
    for (auto ent : _gravityEntities)
    {
        auto& grav = _gravityComponents.Get(ent);

        grav.grounded = false;
    }
}